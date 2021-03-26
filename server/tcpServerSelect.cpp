
/************************************************
#
#      Filename: tcpServer.cpp
#
#        Author: Sh1Yu6
#   Description: ---
#        Create: 2021-03-07 17:24:51
# Last Modified: 2021-03-08 16:35:54
#***********************************************/
#include <iostream>
#include <sys/select.h>
#include <sys/socket.h>
#include <netinet/in.h> // sockaddr_in
#include <arpa/inet.h>
#include <cstring>
#include <unistd.h>
#include <fcntl.h>
using namespace std;

constexpr int kPort = 8888;
constexpr int kBackLog = 10;
constexpr int kMessageLen = 1024;
constexpr int kFdSize = 1024;
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

    //const char* ip = "139.9.5.199";
    //inet_pton(AF_INET, ip, &locaAddr.sin_addr);
    locaAddr.sin_port = htons(kPort);

    //locaAddr.sin_port = kPort;
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

    // accept
    int maxFd = socketFd;
    int acceptFds[kFdSize];
    for(int i = 0; i < kFdSize; ++i){
        acceptFds[i] = -1;
    }
    fd_set fdSets;
    FD_ZERO(&fdSets);

    while(true){

        FD_ZERO(&fdSets);
        FD_SET(socketFd, &fdSets);
        for(int i = 0; i < kFdSize; ++i){
            if(acceptFds[i] != -1){
                if(acceptFds[i] > maxFd){
                    maxFd = acceptFds[i];
                }
                FD_SET(acceptFds[i], &fdSets);
            }
        }

        int events = select(maxFd + 1, &fdSets, nullptr, nullptr, nullptr);

        if(events < 0){
            cout << "Failed to use select!" << endl;
            break;
        }else if(events == 0){
            cout << "timeout..." << endl;
            continue;
        }else if(events){

            if(FD_ISSET(socketFd, &fdSets)){
                int curPos = -1;
                for(int i = 0; i < kFdSize; ++i){
                    if(acceptFds[i] == -1){
                        curPos = i;
                        break;
                    }
                }
                struct sockaddr_in client;
                socklen_t client_addrLength = sizeof(client);
                int acceptFD = accept(socketFd, 
                                     (struct sockaddr*)&client, 
                                     &client_addrLength);

                int flags = fcntl(acceptFD, F_GETFL, 0);
                fcntl(acceptFD, F_SETFL, flags | O_NONBLOCK);
                acceptFds[curPos] = acceptFD;
            }

            for(int i = 0; i < kFdSize; ++i){
                if(acceptFds[i] != -1 && FD_ISSET(acceptFds[i], &fdSets)){
                    char recvBuf[kMessageLen] = {0};
                    ret = recv(acceptFds[i], recvBuf, kMessageLen, 0);
                    if(ret == 0){
                        cout << "break;" << endl;
                        close(acceptFds[i]);
                    }
                    cout << "recv: " << recvBuf << endl;
                    send(acceptFds[i], recvBuf, kMessageLen, 0);

                }
            }
        }
    }

    close(socketFd);
    return 0;
}

