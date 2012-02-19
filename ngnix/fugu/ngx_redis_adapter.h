#ifndef __NGX_REDIS_ADAPTER__
#define __NGX_REDIS_ADAPTER__

// nginx headers
#include <sys/types.h>
#include <ngx_event.h>
#include <ngx_channel.h>

// hiredis headers
#include "hiredis/hiredis.h"
#include "hiredis/async.h"

typedef struct ngx_redis_context_t {
    redisAsyncContext *context;
    ngx_cycle_t* loop;
    ngx_connection_t* conn;
} ngx_redis_context_t;

        
void ngx_redis_read_event_handler(ngx_event_t* handle);
void ngx_redis_write_event_handler(ngx_event_t* handle);
void ngx_redis_add_read(void *privdata);
void ngx_redis_del_read(void *privdata);
void ngx_redis_add_write(void *privdata);
void ngx_redis_del_write(void *privdata);
void ngx_redis_cleanup(void *privdata);
int ngx_redis_attach(ngx_cycle_t* cycle, redisAsyncContext *ac);

#endif
