
/************************************************
#
#      Filename: sigaction.cpp
#
#        Author: Sh1Yu6
#   Description: ---
#        Create: 2021-04-14 13:13:28
# Last Modified: 2021-04-14 13:29:31
#***********************************************/
#include <csignal>
#include <iostream>
#include <signal.h>
#include <unistd.h>

using namespace std;

void func(int signo){
    cout << signo << endl;
    for(int i = 0; i < 5; ++i){
        cout << i << endl;
        sleep(1);
    }
}
int main(int argc, char *argv[])
{
    struct sigaction s;
    s.sa_handler = func;    // 信号处理函数
    sigemptyset(&s.sa_mask); // 阻塞的信号
    sigaction(SIGINT, &s, nullptr);
    while(true){
        sleep(1);
    }
    return 0;
}

