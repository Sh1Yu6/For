
/************************************************
#
#      Filename: nginx.cpp
#
#        Author: Sh1Yu6
#   Description: ---
#        Create: 2021-04-26 14:44:14
# Last Modified: 2021-04-29 15:32:55
#***********************************************/
#include <csignal>
#include <iostream>
#include <signal.h>
#include <unistd.h>
#include <string>
using namespace std;

int main(int argc, char *argv[])
{
    string str;
    while(true){
        cin >> str;
        system(str.c_str());
    }
    return 0;
}

