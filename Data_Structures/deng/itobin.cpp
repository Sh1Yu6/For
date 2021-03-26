
/************************************************
#
#      Filename: itobin.cpp
#
#        Author: Sh1Yu6
#   Description: ---
#        Create: 2021-03-17 07:45:34
# Last Modified: 2021-03-17 07:56:36
#***********************************************/
#include <iostream>
#include <stack>
using namespace std;

int main(int argc, char *argv[])
{

    stack<int> sta;
    int a = 123;
    while(a != 0){
        sta.push(a%2);
        a /= 2;
    }
    while(!sta.empty()){
        cout << sta.top();
        sta.pop();
    }
    cout << endl;
    int b = 100;
    int c = 100 - ((500 -400) >> 2);
    cout << c << endl;
    return 0;

}

