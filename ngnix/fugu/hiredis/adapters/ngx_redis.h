#ifndef __NGX_REDIS_ADAPTER__
#define __NGX_REDIS_ADAPTER__

#include <sys/types.h>
#include <ngx_event.h>
#include <ngx_channel.h>
#include <ngx_config.h>
#include <ngx_core.h>
#include <ngx_http.h>
#include <ngx_core.h>
#include "../hiredis.h"
#include "../async.h"

typedef struct redisNgxEvents {
    redisAsyncContext *context;
    ngx_cycle_t* loop;
    ngx_connection_t* conn;
} redisNgxEvents;

        
void redisNgxReadEvent(ngx_event_t* handle) 
{
    redisNgxEvents *e = (redisNgxEvents*)handle->data;
    redisAsyncHandleRead(e->context);
}

void redisNgxWriteEvent(ngx_event_t* handle) 
{
    redisNgxEvents *e = (redisNgxEvents*)handle->data;
    redisAsyncHandleWrite(e->context);
}

void redisNgxAddRead(void *privdata)
{
    redisNgxEvents *e = (redisNgxEvents*)privdata;
    ngx_handle_read_event(e->conn->read, 0);
    //ngx_add_channel_event(e->loop, e->context->c.fd, NGX_READ_EVENT, redisNgxReadEvent);
}

void redisNgxDelRead(void *privdata)
{
    redisNgxEvents *e = (redisNgxEvents*)privdata;
    ngx_handle_read_event(e->conn->read, NGX_CLEAR_EVENT);
}

void redisNgxAddWrite(void *privdata)
{
    redisNgxEvents *e = (redisNgxEvents*)privdata;
    ngx_handle_write_event(e->conn->write, 0);
    //ngx_add_channel_event(e->loop, e->context->c.fd, NGX_WRITE_EVENT, redisNgxWriteEvent);
}

void redisNgxDelWrite(void *privdata)
{
    redisNgxEvents *e = (redisNgxEvents*)privdata;
    ngx_handle_write_event(e->conn->write, 1);
}

void redisNgxCleanup(void *privdata) 
{
    redisNgxEvents *e = (redisNgxEvents*)privdata;
    redisNgxDelRead(privdata);
    redisNgxDelWrite(privdata);
    free(e);
}

int redisNgxAttach(ngx_cycle_t* cycle, redisAsyncContext *ac)
{  
    //redisContext *c = &(ac->c);
    redisNgxEvents *e;
    
    /* Nothing should be attached when something is already attached */
    if (ac->data != NULL)
        return REDIS_ERR;

    // Create container for context and r/w events
    e = (redisNgxEvents*)malloc(sizeof(*e));
    e->context = ac;
    e->conn = ngx_get_connection(ac->c.fd, cycle->log);
    e->loop = cycle;
    e->conn->read->handler = redisNgxReadEvent;
    e->conn->read->data = e;
    e->conn->write->handler = redisNgxWriteEvent;
    e->conn->write->data = e;
     
    // Register functions to start/stop listening for events
    ac->ev.addRead = redisNgxAddRead;
    ac->ev.delRead = redisNgxDelRead;
    ac->ev.addWrite = redisNgxAddWrite;
    ac->ev.delWrite = redisNgxDelWrite;
    ac->ev.cleanup = redisNgxCleanup;
    ac->ev.data = e;

    //e->conn->read->data = e;
    //e->conn->write->data = e;
    //ngx_add_channel_event(cycle, ac->c.fd, NGX_READ_EVENT, redisNgxReadEvent);
    //ngx_add_channel_event(cycle, ac->c.fd, NGX_WRITE_EVENT, redisNgxWriteEvent);        
    //e->loop = loop;
    
    //ngx_memzero(&e->read, sizeof(ngx_event_t));
    //ngx_memzero(&e->write, sizeof(ngx_event_t));
    //if(ngx_handle_read_event(&e->read, 0) != NGX_OK) {
        //return REDIS_ERR;
    //}
    
    //if(ngx_handle_write_event(&e->write, 0) != NGX_OK) {
        //return REDIS_ERR;
    //}
    
    // Initialize read/write events
    //uv_idle_init(e->loop, &e->write_handle);
    
    //e->reading = e->writing = 0;
    //e->read_handle.data = e;
	//e->write_handle.data = e;

    return REDIS_OK;
}

#endif
