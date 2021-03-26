
/************************************************
#
#      Filename: testSigaction.cpp
#
#        Author: Sh1Yu6
#   Description: ---
#        Create: 2021-03-07 15:08:08
# Last Modified: 2021-03-07 21:10:08
#***********************************************/
#include <iostream>
#include <signal.h>
#include <unistd.h>
using namespace std;

void sigHandler(int sig){
    cout << "received signal: " << sig << endl;
}

int main(int argc, char *argv[])
{
    struct sigaction act, oact;
    act.sa_handler = sigHandler;
    sigfillset(&act.sa_mask);
    act.sa_flags = 0;

    sigaction(SIGINT, &act, &oact);
    pause();
    
    return 0;
}

