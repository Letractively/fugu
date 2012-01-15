#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "hiredis.h"
#include "async.h"
#include "adapters/libuv.h"

#ifdef _WIN32
#include <winsock2.h>
#include <windows.h>
#include <time.h>
#endif

void getCallback(redisAsyncContext *c, void *r, void *privdata) {
    redisReply *reply = r;
    if (reply == NULL) return;
    printf("argv[%s]: %s\n", (char*)privdata, reply->str);

    /* Disconnect after receiving the reply to GET */
    redisAsyncDisconnect(c);
}

void connectCallback(const redisAsyncContext *c) {
    ((void)c);
    printf("connected...\n");
}

void disconnectCallback(const redisAsyncContext *c, int status) {
    if (status != REDIS_OK) {
        printf("Error: %s\n", c->errstr);
    }
    printf("disconnected...\n");
    //aeStop(loop);
}

int main(void) {

	redisContext *ctx = NULL;
	redisReply *reply;

#ifdef _WIN32  
    WSADATA t_wsa; 
    WORD wVers = MAKEWORD(2, 2); // Set the version number to 2.2
    int iError = WSAStartup(wVers, &t_wsa); 

    if(iError != NO_ERROR || LOBYTE(t_wsa.wVersion) != 2 || HIBYTE(t_wsa.wVersion) != 2 ) {
       printf("Winsock2 init error: %d\n", iError);
       exit(1);
    }
    
    atexit((void(*)(void)) WSACleanup);
#endif    

	ctx = redisAsyncConnect("127.0.0.1", 6379);
	redisLibuvAttach(uv_default_loop(), ctx);
    redisAsyncSetConnectCallback(ctx, connectCallback);
    redisAsyncSetDisconnectCallback(ctx, disconnectCallback);
    redisAsyncCommand(ctx, NULL, NULL, "SET key %b", "test", strlen("test"));
    redisAsyncCommand(ctx, getCallback, (char*)"end-1", "GET key");

	uv_run(uv_default_loop());

    return 0;
}
