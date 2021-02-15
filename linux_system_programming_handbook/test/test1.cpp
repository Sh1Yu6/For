
/************************************************
#
#      Filename: test1.cpp
#
#        Author: Sh1Yu6
#   Description: ---
#        Create: 2021-01-30 16:18:32
# Last Modified: 2021-01-30 16:31:08
#***********************************************/
#include <iostream>
#include <sys/time.h>
#include <ctime>
using namespace std;
int main(int argc, char *argv[])
{
    time_t t = time(NULL);
    cout << t << endl;
    tm* aa = localtime(&t);
    cout << aa->tm_hour << endl;
    return 0;
}

