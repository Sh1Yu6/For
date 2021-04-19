
/************************************************
#
#      Filename: signal.cpp
#
#        Author: Sh1Yu6
#   Description: ---
#        Create: 2021-04-14 10:38:14
# Last Modified: 2021-04-14 13:10:11
#***********************************************/
#include <iostream>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <signal.h>
#include <sys/time.h>
using namespace std;

void func(int s){
    cout << s << endl;
    exit(0);
}
int main(int argc, char *argv[])
{
    // 状态: 产生 未决 递达 
    // 按键产生 系统调用 软件条件产生 硬件异常产生 
    // 默认动作 忽略 捕捉(调用用户自定义的处理函数)

    signal(SIGUSR1, func);

    pid_t pid = getpid();

    kill( pid, SIGUSR1 );
    // pid > 0 指定进程
    // pid = 0 同一进程组的所有进程
    // pid < -1 pid的绝对值对应的进程组
    // pid = -1 进程有权限发送的所有进程

    raise(SIGUSR1); // 给自己发信号
    abort();  // 给自己发SIGABRT

    alarm(1); // 指定时间后, 内核给当前进程发送SIGALRM, 默认动作终止, 0取消定时器

    return 0;
}

