
/************************************************
#
#      Filename: socket.cpp
#
#        Author: Sh1Yu6
#   Description: ---
#        Create: 2021-04-16 10:47:24
# Last Modified: 2021-04-16 14:21:31
#***********************************************/
#include <cstdint>
#include <cstdlib>
#include <iostream>
#include <netinet/in.h>
#include <sys/socket.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <arpa/inet.h>
#include <cstring>

using namespace std;

const int kBufSize = 1024;
int main(int argc, char *argv[])
{

    int sockFd = socket(AF_INET, SOCK_STREAM, 0);
    if( sockFd == -1){
        perror( "socket error" );
        exit(1);
    }
    
    sockaddr_in servAddr;
    bzero( &servAddr, sizeof(servAddr) );
    servAddr.sin_port = htons(8888);
    servAddr.sin_addr.s_addr = htonl( INADDR_ANY );

    int ret = bind( sockFd, (sockaddr*)&servAddr, sizeof(servAddr) );
    if( ret == -1 ){
        perror( "bind error" );
        exit(1);
    }

    ret = listen( sockFd, 128 );
    
    if( ret == -1 ){
        perror( "listen error" );
        exit(1);
    }

    while(true){
        sockaddr_in client;
        socklen_t len = sizeof(client);
        int clientFd = accept( sockFd, (sockaddr*)&client, &len );

        pid_t pid = fork();

        if( pid < 0 ){
            perror( "fork error" );
            exit(1);
        }else if( pid > 0 ){
            close( clientFd );
            continue;
        }

        // 子进程处理
        close( sockFd );
        int n = 0;
        char buf[kBufSize];
        memset( buf, 0x00, sizeof(buf) );
        while( ( n = read( clientFd, buf, kBufSize ) ) > 0 ){
            cout << buf << endl;
            memset( buf, 0x00, sizeof(buf) );
        }
        close(clientFd);
        exit(0);
    }

    close( sockFd );
    return 0;
}

