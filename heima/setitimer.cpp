
/************************************************
#
#      Filename: setitimer.cpp
#
#        Author: Sh1Yu6
#   Description: ---
#        Create: 2021-04-14 11:34:09
# Last Modified: 2021-04-14 11:45:32
#***********************************************/
#include <iostream>
#include <sys/time.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <signal.h>
using namespace std;

void func(int signo){
    cout << signo << endl;
}
int main(int argc, char *argv[])
{
    // 设置时钟, 能够周期性触发

    signal(SIGALRM, func);
    struct itimerval tm;
    tm.it_interval.tv_sec = 1;
    tm.it_interval.tv_usec = 0;

    tm.it_value.tv_sec = 3;
    tm.it_value.tv_usec = 0;

    setitimer(ITIMER_REAL, &tm, nullptr);
    while(true){

    }
    return 0;
}

