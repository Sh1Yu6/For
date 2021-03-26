
/************************************************
#
#      Filename: tcpServerLibevent.cpp
#
#        Author: Sh1Yu6
#   Description: ---
#        Create: 2021-03-10 09:58:28
# Last Modified: 2021-03-10 10:16:03
#***********************************************/
#include <event2/event.h>
#include <iostream>
#include <event2/listener.h>
#include <event2/bufferevent.h>
#include <event2/buffer.h>
#include <arpa/inet.h>
#include <cstring>
using namespace std;

constexpr int kPort = 8888;

void onReadCb(struct bufferevent* bev, void* ctx){
    struct evbuffer* input = bufferevent_get_input(bev);
    struct evbuffer* output = bufferevent_get_output(bev);
    evbuffer_add_buffer(output, input);
}

void onAcceptCb(struct evconnlistener* listener, 
                evutil_socket_t fd, 
                struct sockaddr* addr, 
                int sockLen,
                void* ctx){
    struct event_base* base = evconnlistener_get_base(listener);
    struct bufferevent* bev = bufferevent_socket_new(base, fd, 0);
    bufferevent_enable(bev, EV_READ | EV_WRITE);
    bufferevent_setcb(bev, onReadCb, nullptr, nullptr, nullptr);
}

int main(int argc, char *argv[])
{
    struct event_base* base = event_base_new();

    struct sockaddr_in serverAddr;
    bzero(&serverAddr, sizeof(serverAddr));
    serverAddr.sin_family = AF_INET;
    serverAddr.sin_port = htons(kPort);
    serverAddr.sin_addr.s_addr = INADDR_ANY;

    struct evconnlistener* listener = evconnlistener_new_bind(base, 
                                                           onAcceptCb,
                                                           nullptr,
                                                           LEV_OPT_REUSEABLE,
                                                           10,
                                                           (struct sockaddr*)&serverAddr,
                                                           sizeof(serverAddr));

    event_base_dispatch(base);
    return 0;
}

