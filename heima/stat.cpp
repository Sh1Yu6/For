
/************************************************
#
#      Filename: stat.cpp
#
#        Author: Sh1Yu6
#   Description: 文件属性
#        Create: 2021-04-12 15:47:07
# Last Modified: 2021-04-12 16:06:32
#***********************************************/
#include <iostream>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
using namespace std;

int main(int argc, char *argv[])
{
    struct stat s;
    int ret = stat("makefile.txt", &s);
    if(ret == -1){
        perror("open failed: ");
    }
    if(s.st_mode & S_IRUSR){
        cout << "read"<< endl;
    }
    if(s.st_mode & S_IWUSR){
        cout << "write"<< endl;
    }
    if(s.st_mode & S_IXUSR){
        cout << "exec" << endl;
    }

    if((s.st_mode & S_IFMT) == S_IFREG){
        cout << "file" << endl;
    }
    if(S_ISREG(s.st_mode)){
        cout << "file" << endl;
    }
    // st_mode
    // S_IROTH
    // S_IRGRP
    // S_IRUSR
    // S_IRWXO // 掩码
    //
    //
    //
    // file type
    // S_IFSOCK
    // S_IFLNK
    // S_IFREG
    // S_IFBLK
    // S_IFDIR
    // S_IFCHR
    // S_IFIFO
    //
    // S_IFMT 0170000 掩码
    //

    // lstat 获取连接文件本身属性 stat获取指向的文件属性

    return 0;
}

