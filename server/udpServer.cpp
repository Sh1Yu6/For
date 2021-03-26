
/************************************************
#
#      Filename: tcpServer.cpp
#
#        Author: Sh1Yu6
#   Description: ---
#        Create: 2021-03-07 17:24:51
# Last Modified: 2021-03-07 20:50:47
#***********************************************/
#include <iostream>
#include <sys/socket.h>
#include <netinet/in.h> // sockaddr_in
#include <arpa/inet.h>
#include <cstring>
#include <unistd.h>
using namespace std;

constexpr int kPort = 8888;
constexpr int kBackLog = 10;
constexpr int kMessageLen = 1024;
int main(int argc, char *argv[])
{
    // socket
    int socketFd = socket(PF_INET, SOCK_DGRAM, 0);
    if(socketFd == -1){
        cout << "Failed to create socket!" << endl;
        exit(-1);
    }

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
    //ret = listen(socketFd, kBackLog);
    //if(ret == -1){
        //cout << "Failed to listen socket!" << endl;
        //exit(-1);
    //}

    // accept
    //struct sockaddr_in client;
    //socklen_t client_addrLength = sizeof(client);

    while(true){
        struct sockaddr_in client;
        socklen_t client_addrLength = sizeof(client);
        //int acceptFD = accept(socketFd, 
                             //(struct sockaddr*)&client, 
                             //&client_addrLength);
        char recvBuf[kMessageLen] = {0};
        while(true){
            ret = recvfrom(socketFd, 
                           recvBuf, 
                           kMessageLen, 
                           0, 
                           (struct sockaddr*)&client, 
                           &client_addrLength);

            if(ret == 0){
                cout << "break;" << endl;
                break;
            }
            auto clientAddr = inet_ntoa(client.sin_addr);
            auto clientPort = ntohs(client.sin_port);
            cout << "client address: " << clientAddr
                 << "\tclient port: " << clientPort << endl;
            cout << "recv: " << recvBuf << endl;
            sendto(socketFd, recvBuf, ret, 0, (struct sockaddr*)&client, client_addrLength);
        }
    }

    return 0;
}

