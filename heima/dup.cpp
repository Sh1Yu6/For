
/************************************************
#
#      Filename: dup.cpp
#
#        Author: Sh1Yu6
#   Description: 复制文件描述符
#        Create: 2021-04-12 16:26:17
# Last Modified: 2021-04-12 17:06:18
#***********************************************/
#include <iostream>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
using namespace std;

int main(int argc, char *argv[])
{
    // dup2(oldfd, newfd) 如果newfd已经指向文件描述符, 则自动关闭
    // 然后指向oldfd, 
    // 内部计数
    int fd = open("makefile.txt", O_RDWR);
    int fd2 = dup(fd);

    char buf[1024];
    while( read(fd2, buf, 1024) ){
        cout << buf << endl;
    }
    cout << "==========================" << endl;
    lseek(fd, 0, SEEK_SET);
    while( read(fd, buf, 1024) ){
        cout << buf << endl;
    }

    //close(fd2);
    //close(fd);

    // dup2实现重定向

    fd = open( "makefile.txt", O_RDWR );
    dup2( fd, STDOUT_FILENO );
    cout << "aaaaaaaaaaaaaaaaa" << endl;
    close(fd);
    
    return 0;
}

