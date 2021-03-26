
/************************************************
#
#      Filename: merge_sort.cpp
#
#        Author: Sh1Yu6
#   Description: ---
#        Create: 2021-03-15 15:57:13
# Last Modified: 2021-03-15 16:06:45
#***********************************************/
#include <iostream>
#include <algorithm>
using namespace std;


void merge(int low, int mid, int high){

}
void mergeSort(int low, int high){
    if(high - low < 2){
        return;
    }
    int mid = low + (high - low) / 2;
    mergeSort(low, mid);
    mergeSort(mid, high);
    merge(low, mid, high);
}

int main(int argc, char *argv[])
{
    return 0;
}

