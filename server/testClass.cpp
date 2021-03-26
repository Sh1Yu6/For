
/************************************************
#
#      Filename: testClass.cpp
#
#        Author: Sh1Yu6
#   Description: ---
#        Create: 2021-03-07 22:24:43
# Last Modified: 2021-03-07 22:41:49
#***********************************************/
#include <iostream>
#include <signal.h>
#include "tcpServerClass.h"
using namespace std;


int main(int argc, char *argv[])
{

    Sh1Yu6::Server ser;

    ser.setSig(SIGQUIT);
    ser.setSig(SIGINT);

    ser.run();

    return 0;
}

