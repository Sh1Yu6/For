
/************************************************
#
#      Filename: li.cpp
#
#        Author: Sh1Yu6
#   Description: ---
#        Create: 2021-03-27 07:36:58
# Last Modified: 2021-03-27 07:39:20
#***********************************************/
#include <iostream>
#include <list>
#include <vector>
using namespace std;

int main(int argc, char *argv[])
{
    vector<list<int>> v;
    list<int> l{1, 2, 3};
    for(auto i = l.begin(); i != l.end(); ++i){
        cout << *i << endl;
    }
    return 0;
}

