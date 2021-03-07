
/************************************************
#
#      Filename: test2.cpp
#
#        Author: Sh1Yu6
#   Description: ---
#        Create: 2021-02-21 16:19:04
# Last Modified: 2021-02-21 16:22:32
#***********************************************/
#include <iostream>
using namespace std;
void func(int*& a){
    int *b = new int[6]{1, 2, 3, 4, 5, 6};
    for(int i = 0; i < 6; ++i){
        cout << b[i] << endl;
    }
    a = b;
}
int main(int argc, char *argv[])
{
    int *a = new int[6]{11, 22, 33, 44, 55, 66};
    for(int i = 0; i < 6; ++i){
        cout << a[i] << endl;
    }
    func(a);
    for(int i = 0; i < 6; ++i){
        cout << a[i] << endl;
    }
    return 0;
}

