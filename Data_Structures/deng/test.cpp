
/************************************************
#
#      Filename: test.cpp
#
#        Author: Sh1Yu6
#   Description: ---
#        Create: 2021-03-19 19:36:05
# Last Modified: 2021-03-19 19:43:17
#***********************************************/
#include <iostream>
#include <vector>
using namespace std;

int func(vector<int>& v, int key){
    int left = 0;
    int right = v.size() - 1;
    while(left <= right){
        int mid = left + (right - left) / 2;
        if(v[mid] < key){
            left = mid + 1;
        }else if(key < v[mid]){
            right = mid - 1;
        }else{
            return mid;
        }
    }
    return -1;
}
int main(int argc, char *argv[])
{
    vector<int> v{1, 7};
    for(int i = 0; i < 7; ++i){
        cout << v[i] << " ";
        cout << func(v, v[i]) << endl;
    }
    return 0;
}

