
/************************************************
#
#      Filename: fork2.cpp
#
#        Author: Sh1Yu6
#   Description: ---
#        Create: 2021-04-29 19:58:21
# Last Modified: 2021-04-29 20:13:41
#***********************************************/
#include <iostream>
#include <unistd.h>
using namespace std;

int i = 0;
int main(int argc, char *argv[])
{
    cout << sysconf(_SC_CHILD_MAX) << endl;
    fork();
    for(int j = 0; j < 1000000; ++j){
        ++i;
    }
    cout << i << endl;
    cout << &i << endl;
    return 0;
}

