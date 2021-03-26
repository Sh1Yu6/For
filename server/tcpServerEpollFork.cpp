
/************************************************
#
#      Filename: tcpServer.cpp
#
#        Author: Sh1Yu6
#   Description: ---
#        Create: 2021-03-07 17:24:51
# Last Modified: 2021-03-10 08:56:19
#***********************************************/
#include <iostream>
#include <sys/socket.h>
#include <netinet/in.h> // sockaddr_in
#include <arpa/inet.h>
#include <cstring>
#include <sys/epoll.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/wait.h>
using namespace std;

constexpr int kPort = 8888;
constexpr int kBackLog = 10;
constexpr int kMessageLen = 1024;
constexpr int kMaxEvents = 20;
constexpr int kTimeOut = 500;
constexpr int kMaxProcess = 2;
int main(int argc, char *argv[])
{
    // socket
    int socketFd = socket(PF_INET, SOCK_STREAM, 0);
    if(socketFd == -1){
        cout << "Failed to create socket!" << endl;
        exit(-1);
    }
    int flags = fcntl(socketFd, F_GETFL, 0);
    fcntl(socketFd, F_SETFL, flags | O_NONBLOCK);

    int ret = -1;
    int on = 1;
    ret = setsockopt(socketFd, SOL_SOCKET, SO_REUSEADDR, &on, sizeof(on));
    if(ret == -1){
        cout << "Failed to set socket options!" << endl;
        exit(-1);
    }

    // local address and port
    struct sockaddr_in locaAddr;
    bzero(&locaAddr, sizeof(locaAddr));
    locaAddr.sin_family = AF_INET;

    locaAddr.sin_port = htons(kPort);
    locaAddr.sin_addr.s_addr = INADDR_ANY;
    

    // bind
    ret = bind(socketFd, (struct sockaddr*)&locaAddr, sizeof(locaAddr));
    if(ret == -1){
        cout << "Failed to bind addr!" << endl;
        exit(-1);
    }

    // listen
    ret = listen(socketFd, kBackLog);
    if(ret == -1){
        cout << "Failed to listen socket!" << endl;
        exit(-1);
    }

    //fork
    pid_t pid = 1;
    for(int i = 0; i < kMaxProcess; ++i){
        if(pid != 0){
            pid = fork();
        }
    }



    // accept
    if(pid == 0){
        int epollFd = epoll_create(256);

        struct epoll_event ev;
        struct epoll_event events[kMaxEvents];
        ev.events = EPOLLIN;
        ev.data.fd = socketFd;
        epoll_ctl(epollFd, EPOLL_CTL_ADD, socketFd, &ev);
        while(true){

            int eventNum = epoll_wait(epollFd, events, kMaxEvents, kTimeOut);
            for(int i = 0; i < eventNum; ++i){
                if(events[i].data.fd == socketFd){
                    struct sockaddr_in client;
                    socklen_t client_addrLength = sizeof(client);
                    int acceptFD = accept(socketFd, 
                                         (struct sockaddr*)&client, 
                                         &client_addrLength);

                    int flags = fcntl(acceptFD, F_GETFL, 0);
                    fcntl(acceptFD, F_SETFL, flags | O_NONBLOCK);
                    ev.events = EPOLLIN | EPOLLET;
                    ev.data.fd = acceptFD;
                    epoll_ctl(epollFd, EPOLL_CTL_ADD, acceptFD, &ev);
                }else if(events[i].events & EPOLLIN){
                    char recvBuf[kMessageLen] = {0};
                    ret = recv(events[i].data.fd, recvBuf, kMessageLen, 0);
                    if(ret == 0){
                        close(events[i].data.fd);
                        cout << "break;" << endl;
                        break;
                    }
                    if(ret == kMessageLen){
                        cout << "..............." << endl;
                    }
                    if(ret < 0){
                        switch(errno){
                            case EAGAIN:
                                break;
                            case EINTR:
                                break;
                            default:
                                break;
                        }
                    }
                    cout << "recv: " << recvBuf << endl;
                    send(events[i].data.fd, recvBuf, kMessageLen, 0);
                }
            }
        }
        close(socketFd);
    }else{
        do{
            pid = waitpid(-1, nullptr, 0);
        }while(pid != -1);
    }

    return 0;
}

