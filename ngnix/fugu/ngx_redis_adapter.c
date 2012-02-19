#include "ngx_redis_adapter.h"

#include <sys/types.h>
#include <ngx_event.h>
#include <ngx_channel.h>
#include <ngx_config.h>
#include <ngx_core.h>
#include <ngx_http.h>
#include <ngx_core.h>

ngx_int_t ngx_add_redis_event(ngx_cycle_t *cycle, ngx_fd_t fd, ngx_int_t event, ngx_event_handler_pt handler, void* data);


ngx_redis_context_t *ctx;

void ngx_redis_read_event_handler(ngx_event_t* handle) 
{
    //ngx_redis_context_t *e = (ngx_redis_context_t*)handle->data;
    redisAsyncHandleRead(ctx->context);
}

void ngx_redis_write_event_handler(ngx_event_t* handle) 
{
    //ngx_redis_context_t *e = (ngx_redis_context_t*)handle->data;
    redisAsyncHandleWrite(ctx->context);
}

void ngx_redis_add_read(void *privdata)
{
    //ngx_redis_context_t *e = (ngx_redis_context_t*)privdata;
    ngx_add_redis_event(ctx->loop, ctx->context->c.fd, NGX_READ_EVENT, ngx_redis_read_event_handler, privdata);
    //ngx_add_channel_event(ctx->loop, ctx->context->c.fd, NGX_READ_EVENT, ngx_redis_read_event_handler);
}

void ngx_redis_del_read(void *privdata)
{
    //ngx_redis_context_t *e = (ngx_redis_context_t*)privdata;
    ngx_connection_t * conn = ngx_get_connection(ctx->context->c.fd, ctx->loop->log);
    ngx_del_event(conn->read, NGX_READ_EVENT, 0);
}

void ngx_redis_add_write(void *privdata)
{
    //ngx_redis_context_t *e = (ngx_redis_context_t*)privdata;
    ngx_add_redis_event(ctx->loop, ctx->context->c.fd, NGX_WRITE_EVENT, ngx_redis_write_event_handler, privdata);
    //ngx_add_channel_event(ctx->loop, ctx->context->c.fd, NGX_WRITE_EVENT, ngx_redis_write_event_handler);
}

void ngx_redis_del_write(void *privdata)
{
    //ngx_redis_context_t *e = (ngx_redis_context_t*)privdata;
    ngx_connection_t * conn = ngx_get_connection(ctx->context->c.fd, ctx->loop->log);
    ngx_del_event(conn->write, NGX_WRITE_EVENT, 0);
}

void ngx_redis_cleanup(void *privdata)
{
    //ngx_redis_context_t *e = (ngx_redis_context_t*)privdata;
    ngx_redis_del_read(privdata);
    ngx_redis_del_write(privdata);
    //free(e);
}

int ngx_redis_attach(ngx_cycle_t* cycle, redisAsyncContext *ac)
{  
    ngx_redis_context_t *e;
    
    /* Nothing should be attached when something is already attached */
    if (ac->data != NULL)
        return REDIS_ERR;

    // Create container for context and r/w events
    e = (ngx_redis_context_t*)malloc(sizeof(*e));
    e->context = ac;
    e->loop = cycle;

    // Register functions to start/stop listening for events
    ac->ev.addRead = ngx_redis_add_read;
    ac->ev.delRead = ngx_redis_del_read;
    ac->ev.addWrite = ngx_redis_add_write;
    ac->ev.delWrite = ngx_redis_del_write;
    ac->ev.cleanup = ngx_redis_cleanup;
    ac->ev.data = e;
    ctx = e;
    
    /*
    e->conn = ngx_get_connection(ac->c.fd, cycle->log);
    e->conn->read->handler = redisNgxReadEvent;
    e->conn->read->data = e;
    e->conn->write->handler = redisNgxWriteEvent;
    e->conn->write->data = e;
     */
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

ngx_int_t ngx_add_redis_event(ngx_cycle_t *cycle, ngx_fd_t fd, ngx_int_t event, ngx_event_handler_pt handler, void* data)
{
    ngx_event_t       *ev, *rev, *wev;
    ngx_connection_t  *c;

    c = ngx_get_connection(fd, cycle->log);

    if (c == NULL) {
        return NGX_ERROR;
    }

    c->pool = cycle->pool;

    rev = c->read;
    wev = c->write;

    rev->log = cycle->log;
    wev->log = cycle->log;

#if (NGX_THREADS)
    rev->lock = &c->lock;
    wev->lock = &c->lock;
    rev->own_lock = &c->lock;
    wev->own_lock = &c->lock;
#endif

    rev->channel = 1;
    wev->channel = 1;

    ev = (event == NGX_READ_EVENT) ? rev : wev;

    ev->handler = handler;
    
    if (ngx_add_conn && (ngx_event_flags & NGX_USE_EPOLL_EVENT) == 0) {
        if (ngx_add_conn(c) == NGX_ERROR) {
            ngx_free_connection(c);
            return NGX_ERROR;
        }

    } else {
        if (ngx_add_event(ev, event, 0) == NGX_ERROR) {
            ngx_free_connection(c);
            return NGX_ERROR;
        }
    }

    return NGX_OK;
}