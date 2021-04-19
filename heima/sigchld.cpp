
/************************************************
#
#      Filename: signal.cpp
#
#        Author: Sh1Yu6
#   Description: ---
#        Create: 2021-04-14 10:38:14
# Last Modified: 2021-04-15 09:19:06
#***********************************************/
#include <csignal>
#include <iostream>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <signal.h>
#include <sys/time.h>
#include <wait.h>
using namespace std;

void func(int s){
    while(true){
        pid_t wPid = waitpid( -1, nullptr, WNOHANG );
        if( wPid > 0 ){
            cout << wPid << endl;

        }else if( wPid == 0 ){
            cout << 0 << endl;
            break;

        }else if( wPid == -1 ){
            cout << -1 << endl;
            break;
        }

    }
}
int main(int argc, char *argv[])
{

    sigset_t mask;
    sigemptyset( &mask );
    sigaddset( &mask, SIGCHLD );
    sigprocmask( SIG_BLOCK, &mask, NULL );

    int i = 0;
    for(i = 0; i < 3; ++i){
        int p = 0;
        if( ( p = fork() ) == 0 ){
            break;
        }
    }

    if( i == 3 ){
        struct sigaction act;
        act.sa_handler = func;
        sigemptyset( &act.sa_mask );
        act.sa_flags = 0;
        sigaction( SIGCHLD, &act, nullptr );

        sigprocmask( SIG_UNBLOCK, &mask, nullptr );
        while(true){
            sleep(1);
        }
    }

    return 0;
}

