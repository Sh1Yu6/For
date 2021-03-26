
/************************************************
#
#      Filename: test.cpp
#
#        Author: Sh1Yu6
#   Description: ---
#        Create: 2021-03-07 14:20:14
# Last Modified: 2021-03-08 18:01:12
#***********************************************/
#include <iostream>
#include <cstring>
#include <unistd.h>
//#include "iostream"
using namespace std;
int main(int argc, char *argv[])
{

    pid_t t = fork();

    usleep(1000000);
    cout << t << " " << getpid() << endl;
    return 0;
}

