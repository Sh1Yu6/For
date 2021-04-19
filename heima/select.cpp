
/************************************************
#
#      Filename: socket.cpp
#
#        Author: Sh1Yu6
#   Description: ---
#        Create: 2021-04-16 10:47:24
# Last Modified: 2021-04-18 15:33:35
#***********************************************/
#include <asm-generic/errno.h>
#include <asm-generic/socket.h>
#include <cstdint>
#include <iostream>
#include <netinet/in.h>
#include <sys/select.h>
#include <sys/socket.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <arpa/inet.h>
#include <cstring>

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

    //sockaddr_in client;
    //socklen_t clientLen = sizeof(client);
    //int clientFd = accept( sockfd, (sockaddr*)&client, &clientLen );

        // select 委托内核监控文件描述符的变化
        //nfds 监控范围
        //readfds 
        //  告诉内核监控哪些文件描述符
        //  内核告诉应用程序哪些文件描述符发生变化
        //writefds
        //  告诉内核监控哪些文件描述符
        //  内核告诉应用程序哪些文件描述符发生变化
        //exceptfds:
        //  异常事件
        //timeout:
        //   NULL, 阻塞直到有事件发生
        //   0, 不阻塞
        //   >0 阻塞的时长
        //返回值
        //  个数, 几个文件描述符发生变化

        //FD_CLR 清除fd
        //FD_ISSET fd是否存在
        //FD_SET 添加fd
        //FD_ZERO 全部置0

    fd_set readFds;
    fd_set tempFds;
    FD_ZERO( &readFds );
    FD_ZERO( &tempFds );
    FD_SET( sockfd, &readFds );
    int maxFd = sockfd;
    while(true){
        tempFds = readFds;
        int nReady = select( maxFd + 1, &tempFds, nullptr, nullptr, nullptr );
        if( nReady < 0 ){
            if( errno == ECONNABORTED || errno == EINTR ){
                continue;
            }
            perror( "select error" );
            break;
        }

        if( FD_ISSET( sockfd, &tempFds ) ){
            cout << "a" << endl;
            sockaddr_in client;
            socklen_t clientLen = sizeof(client);
            int clientFd = accept( sockfd, (sockaddr*)&client, &clientLen );
            FD_SET( clientFd, &readFds );
            if( maxFd < clientFd ){
                maxFd = clientFd;
            }
            if( --nReady == 0 ){
                continue;
            }
        }

        for(int i = sockfd + 1; i <= maxFd; ++i){
            if( FD_ISSET(i, &tempFds) ){
                char buf[kBufSize];
                //while(true){
                memset( buf, 0x00, kBufSize );
                int n = read( i, buf, kBufSize );
                if( n <= 0 ){
                    close( i );
                    FD_CLR( i, &readFds );
                    break;
                }
                cout << buf << endl;
                //}
            }
        }
    }


    //close(clientFd);
    close(sockfd);
    return 0;
}

