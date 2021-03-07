
/************************************************
#
#      Filename: test.cpp
#
#        Author: Sh1Yu6
#   Description: ---
#        Create: 2021-02-20 14:27:45
# Last Modified: 2021-02-21 16:19:01
#***********************************************/
#include <iostream>
#include <vector>
using namespace std;
int main(int argc, char *argv[])
{
    vector<int> a{1, 2, 3, 4, 5};
    int* b = new int[30];
    int* c = new int{1000};
    int* d = new int{1};
    cout << b << endl;
    cout << c << endl;
    cout << d << endl;

    int* bb{new int[30]};
    int* cc{new int[1000]};
    int* dd{new int{1}};
    cout << bb << endl;
    cout << cc << endl;
    cout << dd << endl;
    return 0;
}

