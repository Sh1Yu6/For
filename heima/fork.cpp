
/************************************************
#
#      Filename: fork.cpp
#
#        Author: Sh1Yu6
#   Description: ---
#        Create: 2021-04-13 13:05:25
# Last Modified: 2021-04-13 17:34:34
#***********************************************/
#include <iostream>
#include <unistd.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
using namespace std;

int main(int argc, char *argv[])
{
    // 僵尸进程
    // 孤儿进程
    int a = 10;
    int pid = 0;
    for(int i = 0; i < 10; ++i){
        if( ( pid = fork() ) == 0 ){
            break;
        }
    }
    for(int i = 0; i < 100000; ++i){
        ++a;
    }

    cout << a << endl;
    return 0;
}

