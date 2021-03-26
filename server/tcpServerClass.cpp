
/************************************************
#
#      Filename: tcpServerClass.cpp
#
#        Author: Sh1Yu6
#   Description: ---
#        Create: 2021-03-07 21:59:02
# Last Modified: 2021-03-07 22:54:20
#***********************************************/
#include <iostream>
#include <netinet/in.h>
#include <sys/socket.h>
#include <unistd.h>
#include <cstring>
#include <signal.h>
#include <fcntl.h>
#include "tcpServerClass.h"
using namespace std;

namespace Sh1Yu6{
    constexpr int kPort = 8888;
    constexpr int kBackLog = 10;
    constexpr int kMessageLen = 1024;

    Server::Server(){
        daemonize();
        init();
    }


    Server::~Server(){
        cout << "close" << endl;
        close(sockFd);
    }

    void Server::init(){
        sockFd = socket(AF_INET, SOCK_STREAM, 0);
        if(sockFd == -1){
            cout << "Failed to create socket!" <<endl;
            exit(-1);
        }

        bzero(&serverAddr, sizeof(serverAddr));
        serverAddr.sin_family = AF_INET;
        serverAddr.sin_port = htons(kPort);
        serverAddr.sin_addr.s_addr = INADDR_ANY;

        int ret = bind(sockFd, 
                       (reinterpret_cast<struct sockaddr*>(&serverAddr)),
                       sizeof(serverAddr));
        if(ret == -1){
            cout << "Failed to bind addr" << endl;
            exit(-1);
        }

        ret = listen(sockFd, kBackLog);
        if(ret == -1){
            cout << "Failed to listen socket" << endl;
            exit(-1);
        }
    }

    void Server::run(){
        while(true){
            struct sockaddr_in client;
            socklen_t clientAddrLen = sizeof(client);
            int acceptFd = accept(sockFd, 
                                  reinterpret_cast<struct sockaddr*>(&client),
                                  &clientAddrLen);
            char recvBuf[kMessageLen] = {0};
            while(true){
                int ret = recv(acceptFd, recvBuf, kMessageLen, 0);
                if(ret == 0){
                    cout << "break;" << endl;
                    break;
                }
                cout << "recv: " << recvBuf << endl;
                send(acceptFd, recvBuf, strlen(recvBuf), 0);
            }
        }
    }

    void func(int sig){
        cout << "SIG: " << sig << endl;
    }

    void Server::setSig(int sig){
        signal(sig, func);
    }

    void Server::daemonize(){
        if(pid_t pid; (pid = fork()) < 0){
            cout << "can't create subprocess!" << endl;
        }else{
            if(pid != 0){
                exit(0);
            }
        }

        setsid();

        if( chdir("/") < 0 ){
            cout << "can't change dir!" << endl;
            exit(-1);
        }

        int fd = open("/dev/null", O_RDWR);
        dup2(fd, STDIN_FILENO);
        dup2(fd, STDOUT_FILENO);
        dup2(fd, STDERR_FILENO);

        return;
    }
}
