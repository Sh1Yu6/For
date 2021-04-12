
/************************************************
#
#      Filename: fcntl.cpp
#
#        Author: Sh1Yu6
#   Description: 改变已打开文件的属性
#        Create: 2021-04-12 17:00:56
# Last Modified: 2021-04-12 17:13:48
#***********************************************/
#include <iostream>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <cstring>
using namespace std;

int main(int argc, char *argv[])
{
    //fcntl();
    //F_DUPFD
    //F_GETFL 获取文件描述符flag属性
    //F_SETFL 设置文件描述符flag属性
    //O_APPEND O_NONBLOCK
    //
    int fd = open("makefile.txt", O_WRONLY);
    int flag = fcntl(fd, F_GETFL, 0);
    flag = flag | O_APPEND;
    fcntl(fd, F_SETFL, flag);
    write(fd, "abc",  strlen("abc"));
    close(fd);
    return 0;
}

