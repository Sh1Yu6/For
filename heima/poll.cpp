
/************************************************
#
#      Filename: socket.cpp
#
#        Author: Sh1Yu6
#   Description: ---
#        Create: 2021-04-16 10:47:24
# Last Modified: 2021-04-18 17:15:10
#***********************************************/
#include <cstdint>
#include <iostream>
#include <netinet/in.h>
#include <sys/poll.h>
#include <sys/select.h>
#include <sys/socket.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <arpa/inet.h>
#include <cstring>
#include <poll.h>

using namespace std;

constexpr int kBufSize = 1024;

int main(int argc, char *argv[])
{

    sockaddr_in sockAddr;
    bzero(&sockAddr, sizeof(sockAddr));
    sockAddr.sin_family = AF_INET;
    //inet_pton(AF_INET, "127.0.0.1", &sockAddr.sin_addr.s_addr);
    sockAddr.sin_addr.s_addr = htonl(INADDR_ANY);
    sockAddr.sin_port = htons(8888);
    
    int sockfd = socket(AF_INET, SOCK_STREAM, 0);
    // SOCK_STREAM, SOCK_DGRAM
    if( sockfd == -1 ){
        perror( "sockket error" );
    }
    int op = 1;
    setsockopt( sockfd, SOL_SOCKET, SO_REUSEADDR, &op, sizeof(op) );

    int ret = bind( sockfd, (sockaddr*)&sockAddr, sizeof(sockAddr) );
    if( ret == -1 ){
        perror( "bind error" );
    }

    ret = listen( sockfd, 128 );
    if( ret == -1 ){
        perror( "listen error" );
    }

    struct pollfd clients[1024];
    clients[0].fd = sockfd;
    clients[0].events = POLLIN;

    int maxNum = 0;
    for(int i = 1; i < 1024; ++i){
        clients[i].fd = -1;
    }

    while(true){
        int nReady = poll(clients, maxNum + 1, -1);
        if( nReady < 0 ){
            if( errno == EINTR || errno == ECONNABORTED ){
                continue;
            }
            break;
        }

        if( clients[0].revents == POLLIN ){
            sockaddr_in client;
            socklen_t clientLen = sizeof(client);
            int clientFd = accept( sockfd, (struct sockaddr*)&client, 
                                  &clientLen);
            int i = 0;
            for( ; i < 1024; ++i ){
                if(clients[i].fd == -1){
                    clients[i].fd = clientFd;
                    clients[i].events = POLLIN;
                    cout << i << "jjj " << clients[i].fd << endl;
                    break;
                }
            }

            if( i == 1024 ){
                close(clientFd);
                continue;
            }

            if( maxNum < i ){
                maxNum = i;
            }

            cout << nReady << endl;
            if( --nReady == 0 ){
                continue;
            }
        }

        for( int i = 1; i <= maxNum; ++i){
            if(clients[i].fd == -1){
                continue;
            }
            if( clients[i].revents == POLLIN ){
                char buf[kBufSize];
                memset(buf, 0x00, kBufSize);
                int n = read(clients[i].fd, buf, kBufSize);
                if( n <= 0 ){
                    int tempFd = clients[i].fd;
                    clients[i].fd = clients[maxNum].fd;
                    close(tempFd);
                    clients[maxNum].fd = -1;
                    --maxNum;
                    --i;
                    continue;
                }
                cout << buf << endl;
            }
        }
    }


    //close(clientFd);
    close(sockfd);
    return 0;
}

