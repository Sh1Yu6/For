
/************************************************
#
#      Filename: tcpClient.cpp
#
#        Author: Sh1Yu6
#   Description: ---
#        Create: 2021-03-07 19:56:18
# Last Modified: 2021-03-07 21:02:08
#***********************************************/
#include <iostream>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <cstring>
//#include <sys/types.h>
using namespace std;

constexpr int kPort = 8888;
constexpr int kMessageLen = 1024;
int main(int argc, char *argv[])
{
    int socketFd = socket(PF_INET, SOCK_DGRAM, 0);
    if(socketFd == -1){
        cout << "Failed to create socket!" << endl;
        exit(-1);
    }

    struct sockaddr_in serverAddr;
    serverAddr.sin_family = AF_INET;
    serverAddr.sin_port = htons(kPort);
    serverAddr.sin_addr.s_addr = inet_addr("127.0.0.1");
    
    socklen_t len = sizeof(struct sockaddr);

    //int ret = connect(socketFd, 
                     //(struct sockaddr*)&serverAddr, 
                     //sizeof(struct sockaddr));
    //if(ret < 0){
        //cout << "Failed to connect server!" << endl;
        //exit(-1);
    //}

    int ret = -1;
    char sendBuf[kMessageLen] = {"hello, world!"};
    char recvBuf[kMessageLen];

    while(true){
        ret = sendto(socketFd, sendBuf, kMessageLen, 0, (struct sockaddr*)&serverAddr, len);
        if(ret <= 0){
            cout << "Failed to send data!" << endl;
            break;
        }
        ret = recvfrom(socketFd, recvBuf, kMessageLen, 0, (struct sockaddr*)&serverAddr, &len);
        recvBuf[ret] = '\0';
        cout << recvBuf << endl;
        usleep(2000000);
    }
    close(socketFd);

    return 0;
}

