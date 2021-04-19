
/************************************************
#
#      Filename: biglittle.cpp
#
#        Author: Sh1Yu6
#   Description: ---
#        Create: 2021-04-16 10:57:49
# Last Modified: 2021-04-16 10:59:23
#***********************************************/
#include <iostream>
using namespace std;

union u{
    short s;
    char c[ sizeof(short) ];
};

int main(int argc, char *argv[])
{
    u temp;
    temp.s = 0x0102;
    cout << (int)temp.c[0] << endl;
    return 0;
}

