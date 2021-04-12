
/************************************************
#
#      Filename: error.cpp
#
#        Author: Sh1Yu6
#   Description: ---
#        Create: 2021-04-12 14:35:29
# Last Modified: 2021-04-12 15:11:55
#***********************************************/
#include <iostream>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <errno.h>
using namespace std;

int main(int argc, char *argv[])
{
    // 普通文件非阻塞
    // 设备文件是阻塞的
    // socket pipe阻塞
    int fd = open("/dev/tty", O_RDWR);
    if( fd < 0 ){
        perror("open failed:");
    }
    char buff[1024];
    int count = 0;
    while( ( count = read( fd, buff, 1024 ) ) ){
        write(STDOUT_FILENO, buff, count);
        // STDIN_FILENO
        // STDOUT_FILENO
        // STDERR_FILENO
    }
    cout << "a" << endl;
    close(fd);
    return 0;
}

