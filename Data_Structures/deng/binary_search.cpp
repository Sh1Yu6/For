
/************************************************
#
#      Filename: binary_search.cpp
#
#        Author: Sh1Yu6
#   Description: ---
#        Create: 2021-03-15 12:12:57
# Last Modified: 2021-03-15 12:42:26
#***********************************************/
#include <iostream>
#include <algorithm>
using namespace std;

int binarySearch(int *a, int low, int high, int key){
    while(low < high){
        int mid = low + (high - low) / 2; 
        if( key < a[mid] ){
            high = mid;
        }else if( a[mid] < key ){
            low = mid + 1;
        }else{
            return mid;
        }
    }
    return -1;

}
int main(int argc, char *argv[])
{
    //int a[] = {1, 2, 3, 4, 5, 6, 7, 8, 9};
    int a[] = {1, 2};
    cout << binarySearch(a, 0, 2, 2) << endl;

    return 0;
}

