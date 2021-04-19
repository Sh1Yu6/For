
/************************************************
#
#      Filename: pipe.cpp
#
#        Author: Sh1Yu6
#   Description: ---
#        Create: 2021-04-13 20:08:42
# Last Modified: 2021-04-14 09:34:23
#***********************************************/
#include <cstdlib>
#include <iostream>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <cstring>
#include <wait.h>

using namespace std;

int main(int argc, char *argv[])
{
    // pipe 只能在父子或者兄弟进程之间通信
    // 要读的关闭写端, 要写的关闭读端
    // fifo 无血缘关系的进程通信
    // mmap 有血缘或者无血缘
    // 文件 管道 信号 共享内存 消息队列 套接字 命名管道
    
    // 1. 创建一个fifo文件: mkfifo 或 mkfifo函数
    // 2. open fifo
    // 3. write
    // 4. close

    // 1. open fifo
    // 2. read fifo
    // 3. close 

    // access 
    int ret = access( "./myfifo", F_OK );
    if( ret != 0 ){
        ret = mkfifo( "./myfifo", 0777 );
        if( ret < 0 ){
            perror( "mkfifo error" );
            return -1;
        }
    }

    int fd = open("./myfifo", O_WRONLY);
    if( fd < 0 ){
        perror( "open error" );
        return -1;
    }
    write( fd, "abc", 3 );
    close(fd);
    return 0;
}

