
/************************************************
#
#      Filename: signal_set.cpp
#
#        Author: Sh1Yu6
#   Description: ---
#        Create: 2021-04-14 13:10:21
# Last Modified: 2021-04-14 13:12:47
#***********************************************/
#include <iostream>
#include <signal.h>
using namespace std;

int main(int argc, char *argv[])
{
    sigset_t set;

    sigemptyset(&set);
    sigaddset( &set, SIGINT );
    sigaddset( &set, SIGQUIT );

    sigprocmask( SIG_BLOCK, &set, nullptr );
    return 0;
}

