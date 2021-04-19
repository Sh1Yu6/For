
/************************************************
#
#      Filename: pipe.cpp
#
#        Author: Sh1Yu6
#   Description: ---
#        Create: 2021-04-13 20:08:42
# Last Modified: 2021-04-13 21:15:18
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
    
    // pipe 只能在父子或者兄弟进程之间通信
    // 1. 本质是一块内核缓冲区
    // 2. 读写两端, 是两个文件描述符
    // 3. 只能单向流动 读写都是阻塞
    // 0 读 1 写
    int fd[2];
    int ret = pipe(fd);
    if(ret < -1){
        perror("pipe error");
        return -1;
    }

    // 写端全关闭
    // read非阻塞, 返回0
    // 读端全关闭
    // 管道破裂, 进程终止, 内核给当前进程发SIGPIPE信号S
    // 设置非阻塞
    // int flags = fcnt(fd[0], F_GETFL, 0);
    // flags |= O_NONBLOCK;
    // fcntl(fd[0], F_SETFL, flags);

    pid_t pid = fork();
    if( pid < 0 ){
        perror( "fork error" );
        return -1;
    }else if( pid > 0 ){
        close(fd[0]);
        dup2(fd[1], STDOUT_FILENO);
        execlp("ps", "ps", "-aux", nullptr);
        //write(fd[1], "abc skdfj", strlen("abc skdfj"));
        wait(nullptr);
    }else{
        close(fd[1]);
        dup2(fd[0], STDIN_FILENO);
        //char buf[1024];
        //memset(buf, 0x00, sizeof(buf));
        //int n;
        //while( (n = read(fd[0], buf, 1024)) != 0 ){
            //cout << buf<< endl;
            //memset(buf, 0x00, sizeof(buf));
        //}
        execlp("grep", "grep", "bash", nullptr);
    }

    return 0;
}

