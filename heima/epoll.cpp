
/************************************************
#
#      Filename: socket.cpp
#
#        Author: Sh1Yu6
#   Description: ---
#        Create: 2021-04-16 10:47:24
# Last Modified: 2021-04-19 13:25:31
#***********************************************/
#include <cstdint>
#include <iostream>
#include <netinet/in.h>
#include <sys/socket.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <arpa/inet.h>
#include <cstring>
#include <sys/epoll.h>

using namespace std;

constexpr int kBufSize = 5;

int main(int argc, char *argv[])
{
    // 创建socket
    // 设置端口复用
    // ip地址端口设置
    // bind
    // 监听listren

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

    

    //epoll_create(1024);
    // size:  传大于0的数
    // 返回一个文件描述符, 表示epoll树的根结点
    //
    // 
    // epoll_ctl 对epoll树管理
    // epfd 根
    // op EPOLL_CTL_ADD EPOLL_CTL_MOD EPOLL_CTL_DEL
    // fd 
    // event EPOLLIN EPOLLOUT EPOLLERR
    //
    // epoll_wait 委托内核监控 
    //
    // LT 缓冲区有数据就一直通知
    // ET 只会通知一次, 如果数据没读完, 会等到下次有事件发生继续读
    int epfd = epoll_create(1024);

    struct epoll_event ev;
    ev.events = EPOLLIN;
    ev.data.fd = sockfd;
    epoll_ctl( epfd, EPOLL_CTL_ADD, sockfd, &ev );

    struct epoll_event events[1024];
    while(true){
        int nReady = epoll_wait( epfd, events, 1024, -1);
        if( nReady < 0){
            if( errno == EINTR || errno == ECONNABORTED ){
                continue;
            }
            break;
        }

        for( int i = 0; i < nReady; ++i ){

            int fd = events[i].data.fd;

            // 链接请求
            if( fd == sockfd ){
                sockaddr_in client;
                socklen_t clientLen = sizeof(client);
                int clientFd = accept(sockfd, (sockaddr*)&client, &clientLen);
                ev.data.fd = clientFd;
                ev.events = EPOLLIN;
                epoll_ctl( epfd, EPOLL_CTL_ADD, clientFd, &ev );
                continue;
            }

            // 通信数据
            while(true){

                char buf[kBufSize];
                memset(buf, 0x00, kBufSize);
                int n = read( fd, buf, kBufSize );
                // 如果是阻塞 读完数据会堵塞, 不能正常结束
                // 非阻塞 读完数据返回 -1
                // 0 对方关闭
                if( n == 0 ){
                    close( fd );
                    epoll_ctl ( epfd, EPOLL_CTL_DEL, fd, nullptr );
                    continue;
                }
                cout << buf << endl;
            }

        }
    }


    close(sockfd);
    return 0;
}

