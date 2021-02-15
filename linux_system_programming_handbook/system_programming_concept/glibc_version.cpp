
/************************************************
#
#      Filename: glibc_version.cpp
#
#        Author: Sh1Yu6
#   Description: ---
#        Create: 2021-01-25 14:36:37
# Last Modified: 2021-01-25 14:37:40
#***********************************************/
#include <iostream>
#include <gnu/libc-version.h>
using namespace std;
int main(int argc, char *argv[])
{
    auto str = gnu_get_libc_version();
    cout << str << endl;
    return 0;
}

