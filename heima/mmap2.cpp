
/************************************************
#
#      Filename: pipe.cpp
#
#        Author: Sh1Yu6
#   Description: ---
#        Create: 2021-04-13 20:08:42
# Last Modified: 2021-04-14 10:16:59
#***********************************************/
#include <cstdlib>
#include <iostream>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <cstring>
#include <wait.h>
#include <sys/mman.h>


using namespace std;

int main(int argc, char *argv[])
{
    // pipe 只能在父子或者兄弟进程之间通信
    // 要读的关闭写端, 要写的关闭读端
    // fifo 无血缘关系的进程通信
    // mmap 有血缘或者无血缘
    // 文件 管道 信号 共享内存 消息队列 套接字 命名管道

    // mmap
    // addr 一般NULL, 让内核指定起始地址
    // length 文件大小
    // prot PROT_READ PROT_WRITE
    // flags MAP_SHARED MAP_PRIVATE 
    // fd 需要映射的文件描述符
    // offset 从哪里开始映射, 一般0
    // 返回映射区的首地址
    int fd = open("./test.txt", O_RDWR | O_CREAT, 0666);
    if( fd < 0 ){
        perror( "open error" );
        return -1;
    }

    int len = lseek(fd, 0, SEEK_END);

    void* addr = mmap( nullptr, len, PROT_READ | PROT_WRITE, MAP_SHARED, 
            fd, 0);
    if( addr == MAP_FAILED ){
        perror( "mmap error" );
        return -1;
    }

    pid_t pid = fork();
    if( pid < 0 ){
        perror( "fork error" );
        return -1;
    }else if( pid > 0 ){
        memcpy(addr, "abc", 3);
        wait(nullptr);
    }else{
        sleep(1);
        char* p = (char*) addr;
        cout << p << endl;
    }
    return 0;
}

