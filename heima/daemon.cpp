
/************************************************
#
#      Filename: daeman.cpp
#
#        Author: Sh1Yu6
#   Description: ---
#        Create: 2021-04-15 10:16:02
# Last Modified: 2021-04-30 15:21:56
#***********************************************/
#include <iostream>
#include <cstdio>
#include <pthread.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <time.h>
#include <signal.h>
#include <sys/time.h>
#include <cstring>
using namespace std;

void func(int signo){
    int fd = open( "./daemon.txt", O_RDWR | O_CREAT | O_APPEND, 0777 );

    time_t t = time( nullptr );
    char* p = ctime( &t );
    write( fd, p, strlen(p) );
    close(fd);
}
int main(int argc, char *argv[])
{
    // 1 创建子进程 父进程退出
    pid_t pid = fork();
    if( pid < 0 ){
        perror( "fork error" );
        return -1;
    }
    if( pid > 0 ){
        exit(0);
    }

    // 2 子进程调用setsid()
    setsid();

    // 3 改变工作目录

    chdir( "/home/wang/" );

    // 4 重设文件掩码
    umask(0000);

    // 5 关闭文件描述符
    close( STDIN_FILENO );
    close( STDOUT_FILENO );
    close( STDERR_FILENO );

    // 6 执行工作

    struct sigaction act;
    act.sa_handler = func;
    act.sa_flags = 0;
    sigemptyset( &act.sa_mask );
    sigaction( SIGALRM, &act, nullptr );

    struct itimerval tm;
    tm.it_interval.tv_sec = 2;
    tm.it_interval.tv_usec = 0;
    tm.it_value.tv_sec = 3;
    tm.it_value.tv_usec = 0;

    setitimer( ITIMER_REAL, &tm, nullptr );

    while(true){
        sleep(1);
    }
    return 0;
}

