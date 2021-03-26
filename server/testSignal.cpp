
/************************************************
#
#      Filename: testSIG.cpp
#
#        Author: Sh1Yu6
#   Description: ---
#        Create: 2021-03-07 14:52:06
# Last Modified: 2021-03-07 22:36:21
#***********************************************/
#include <csignal>
#include <iostream>
#include <signal.h>
#include <unistd.h>
using namespace std;

void sigHandle(int sig){
    cout << "receved signal: " << sig << endl;
}


void func(){
    signal(SIGINT, sigHandle);
    signal(SIGHUP, sigHandle);
}
int main(int argc, char *argv[])
{
    func();
    while(true){
        cout << "asdasdasd" << endl;
        usleep(2000000);
    }
    return 0;
}

