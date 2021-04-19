
/************************************************
#
#      Filename: fork.cpp
#
#        Author: Sh1Yu6
#   Description: ---
#        Create: 2021-04-13 13:05:25
# Last Modified: 2021-04-13 18:07:19
#***********************************************/
#include <cstdlib>
#include <iostream>
#include <sys/wait.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <wait.h>
using namespace std;

int main(int argc, char *argv[])
{

    // waitpid(pid, status, options);
    // pid == -1 相当有wait
    // pid > 0 等待与pid相等的进程
    // pid = 0 等待组进程id与目前进程相同的任何子进程
    // pid < -1 等待其组ID等于pid的绝对值的任一子进程
    // options WNOHANG 非阻塞   0 阻塞
    // 返回值 >0 回收的子进程pid  -1 无子进程 0 非阻塞状态 子进程正在运行
    

    int n = 3;
    int pid = 0;
    int a = 1; 
    for(int i = 0; i < n; ++i){
        a += 2;
        if( ( pid = fork()) == 0 ){
            break;
        }
    }
    if( pid > 0 ){
        cout << "father:" << getpid() << endl;

        while(n--){
            int status = 0; // 子进程退出状态

            pid_t waitPid = wait(&status);
            if( WIFEXITED(status) ){
                cout << "normal" << endl;
            }else if( WIFSIGNALED(status) ){
                cout << "signal" << endl;
            }

            //  normal exit WIFEXITED(status);
            // killed by signal WIFSIGNALED(status);
            cout << waitPid << endl;
        }
    }else{
        sleep(a);
        cout << "child:" << getpid() << endl;
        return 0;
    }

    return 0;
}

