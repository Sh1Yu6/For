
/************************************************
#
#      Filename: socket.cpp
#
#        Author: Sh1Yu6
#   Description: ---
#        Create: 2021-04-16 10:47:24
# Last Modified: 2021-04-16 12:21:05
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

using namespace std;

int main(int argc, char *argv[])
{

    sockaddr_in sockAddr;
    bzero(&sockAddr, sizeof(sockAddr));
    sockAddr.sin_family = AF_INET;
    inet_pton(AF_INET, "127.0.0.1", &sockAddr.sin_addr.s_addr);
    // sockAddr.sin_addr.s_addr = htonl(INADDR_ANY);
    sockAddr.sin_port = htons(8888);
    
    int sockfd = socket(AF_INET, SOCK_STREAM, 0);
    // SOCK_STREAM, SOCK_DGRAM
    if( sockfd == -1 ){
        perror( "sockket error" );
    }

    int ret = bind( sockfd, (sockaddr*)&sockAddr, sizeof(sockAddr) );
    ret = listen( sockfd, 5 );

    sockaddr_in client;
    socklen_t clientLen = sizeof(client);
    int clientFd = accept( sockfd, (sockaddr*)&client, &clientLen );

    cout << inet_ntoa(client.sin_addr) << endl;
    cout << ntohs(client.sin_port) << endl;
    cout << client.sin_family << endl;
    int n = 0;
    char buf[1024];
    memset( buf, 0x00, sizeof(buf) );
    // connect( fd, dst, size );
    // read
    // write
    // recv
    // send
    close(sockfd);
    close(clientFd);
    return 0;
}

