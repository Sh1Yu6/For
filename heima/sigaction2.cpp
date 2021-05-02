
/************************************************
#
#      Filename: sigaction2.cpp
#
#        Author: Sh1Yu6
#   Description: ---
#        Create: 2021-04-29 19:04:35
# Last Modified: 2021-04-29 19:27:19
#***********************************************/
#include <iostream>
#include <unistd.h>
#include <signal.h>
using namespace std;

void func(int signo){
    cout << signo << endl;
}
int main(int argc, char *argv[])
{
    sigset_t newMask, oldMask;

    if( signal(SIGQUIT, func) == SIG_ERR ){
        cout << "Unable to capture SIGQUIT" << endl;
        exit(1);
    }

    sigemptyset( &newMask );
    //sigfillset( &oldMask );
    sigaddset( &newMask, SIGQUIT );

    if( sigprocmask( SIG_BLOCK, &newMask, &oldMask ) < 0){
        cout << "sigprocmask error" << endl;
        exit(1);
    }


    sleep(2);

    if( sigismember( &newMask, SIGQUIT ) ){
        cout << "SIGQUIT is blocked" << endl;
    }else{
        cout << "SIGQUIT is not blocked" << endl;
    }

    if( sigprocmask( SIG_SETMASK, &oldMask, nullptr ) < 0 ){
        cout << "sigprocmake error" << endl;
        exit(1);
    }




    return 0;
}

