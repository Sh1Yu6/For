
/************************************************
#
#      Filename: file.cpp
#
#        Author: Sh1Yu6
#   Description: ---
#        Create: 2021-04-12 13:26:01
# Last Modified: 2021-04-12 14:31:13
#***********************************************/
#include <iostream>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <cstdio>
#include <cstring>
using namespace std;

constexpr int kBuffSize = 1024;
int main(int argc, char *argv[])
{
    int fd = open("makefile.txt", O_RDWR);
    // O_RDWR O_RDONLY O_WRONLY O_APPEND O_TRUNC O_CREATE
    // O_NONBLOCK
    // 0777 0是8进制的意思
    // mode & ~umask

    if(fd < 0){
        cerr << " Failed to open file!" << endl;
    }
    char buff[kBuffSize];
    int count = 0;
    while( (count = read(fd, buff, kBuffSize) )){
        write(1, buff, count);
    }

    cout << "-------------------------------------------" << endl;
    lseek(fd, 0, SEEK_SET);
    // SEEK_SET SEEK_CUR SEEK_END
    off_t fileSize = lseek(fd, 0, SEEK_END);
    cout << fileSize << endl;
    close(fd);

    return 0;
}

