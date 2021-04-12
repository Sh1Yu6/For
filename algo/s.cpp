
/************************************************
#
#      Filename: s.cpp
#
#        Author: Sh1Yu6
#   Description: ---
#        Create: 2021-03-27 20:34:50
# Last Modified: 2021-03-27 20:36:02
#***********************************************/
#include <iostream>
#include <algorithm>
#include <string>
using namespace std;

int main(int argc, char *argv[])
{
    string a{ "ajsdkfljaskdlf" };
    reverse(a.begin(), a.end());
    cout << a << endl;
    return 0;
}

