
/************************************************
#
#      Filename: socket.cpp
#
#        Author: Sh1Yu6
#   Description: ---
#        Create: 2021-04-16 10:47:24
# Last Modified: 2021-04-16 14:42:42
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
#include <pthread.h>

using namespace std;

const int kBufSize = 1024;
void* func(void* clifd){
    // 子进程处理
    int clientFd = *(int*)clifd;
    int n = 0;
    char buf[kBufSize];
    memset( buf, 0x00, sizeof(buf) );
    while( ( n = read( clientFd, buf, kBufSize ) ) > 0 ){
        cout << clientFd << endl;
        cout << buf << endl;
        memset( buf, 0x00, sizeof(buf) );
    }
    close(clientFd);
    cout << "end" << endl;
    pthread_exit(nullptr);
}
int main(int argc, char *argv[])
{

    int sockFd = socket(AF_INET, SOCK_STREAM, 0);
    if( sockFd == -1){
        perror( "socket error" );
        exit(1);
    }

    int opt = 1;
    setsockopt( sockFd, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt) );
    
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
        if( clientFd == -1 ){
            if( errno == ECONNABORTED || errno == EINTR ){
                continue;
            }else{
                perror("accept error");
            }
        }
        pthread_t p;
        pthread_create( &p, nullptr, func, &clientFd );
        cout << &p << endl;
        pthread_detach( p );
    }

    close( sockFd );
    return 0;
}

