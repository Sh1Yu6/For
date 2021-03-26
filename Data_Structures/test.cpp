
/************************************************
#
#      Filename: test.cpp
#
#        Author: Sh1Yu6
#   Description: ---
#        Create: 2021-03-20 09:46:34
# Last Modified: 2021-03-20 09:48:47
#***********************************************/
#include <iostream>
#include <vector>
using namespace std;

int main(int argc, char *argv[])
{
    vector<int> a(3, 10);
    vector<vector<int>> b(5);
    for(auto i: b){
        for(auto j: i){
            cout << j << " ";
        }
        cout << endl;
    }

    return 0;
}

