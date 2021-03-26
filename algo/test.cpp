
/************************************************
#
#      Filename: test.cpp
#
#        Author: Sh1Yu6
#   Description: ---
#        Create: 2021-03-22 15:27:16
# Last Modified: 2021-03-26 07:12:37
#***********************************************/
#include <iostream>
#include <algorithm>
#include "sort_test_helper.h"
using namespace std;

template<typename T>
void selectionSort(T* arr, int n){
    for(int i = 0; i < n; ++i){
        int minIndex = i;
        for(int j = i + 1; j < n; ++j ){
            if( arr[j] < arr[minIndex] ){
                minIndex = j;
            }
        }
        swap( arr[i], arr[minIndex] );
    }
}



template<typename T>
void insertionSort(T* arr, int n){
    for(int i = 1; i < n; ++i){
        for(int j = i; j > 0; --j){
            if(arr[j] < arr[j - 1]){
                swap( arr[j], arr[j - 1] );
            }else{
                break;
            }
        }
    }
}



template<typename T>
void merge(T* arr, int left, int mid, int right){

    T aux[right - left + 1];

    for(int i = left; i <= right; ++i){
        aux[i - left] = arr[i];
    }

    int i = left, j = mid + 1;

    for(int k = left; k <= right; ++k){

        if(i > mid){
            arr[k] = aux[j - left];
            ++j;
        }else if( j > right ){
            arr[k] = aux[i - left];
            ++i;
        }else if(aux[i-left] < aux[j-left]){
            arr[k] = aux[i-left];
            ++i;
        }else{
            arr[k] = aux[j-left];
            ++j;
        }
    }

}


template<typename T>
void mergeS(T* arr, int left, int right){
    if(left >= right){
        return;
    }

    int mid = left + (right - left) / 2;
    mergeS(arr, left, mid);
    mergeS(arr, mid + 1, right);
    if(arr[mid] > arr[mid+1]){
        merge(arr, left, mid, right);
    }
}

template<typename T>
void mergeSort(T* arr, int n){
    mergeS(arr, 0, n - 1);
}







template<typename T>
int partition(T* arr, int left, int right){
    //T v = arr[left];
    //int j = left;
    //for(int i = left + 1; i <= right; ++i){
        //if(arr[i] < v){
            //swap( arr[j + 1], arr[i] );
            //++j;
        //}
    //}
    //swap( arr[left], arr[j] );
    //return j;

    T v = arr[left];
    int i = left;
    int j = right;
    while(i < j){
        while(i < j && arr[j] >= v){
            --j;
        }
        if( i < j ){
            arr[i++] = arr[j];
        }
        while(i < j && arr[i] <= v){
            ++i;
        }
        if( i < j ){
            arr[j--] = arr[i];
        }
    }
    arr[i] = v;
    return i;
}

template<typename T>
void quickS(T* arr, int left, int right){
    if(left >= right){
        return;
    }

    int p = partition(arr, left, right);

    quickS(arr, left, p - 1);
    quickS(arr, p + 1, right);
}

template<typename T>
void quickSort(T* arr, int n){
    quickS(arr, 0, n - 1);
}







int main(int argc, char *argv[])
{
    int n = 10;
    auto arr = SortTestHelper::generateRandomArray(n, 0, n);
    auto arr2 = SortTestHelper::copyArray(arr, n);
    auto arr3 = SortTestHelper::copyArray(arr, n);
    auto arr4 = SortTestHelper::copyArray(arr, n);

    SortTestHelper::testSort("Selection Sort", selectionSort, arr, n);
    SortTestHelper::testSort("Insertion Sort", insertionSort, arr2, n);
    SortTestHelper::testSort("Merge Sort", mergeSort, arr3, n);
    SortTestHelper::testSort("Quick Sort", quickSort, arr4, n);
    SortTestHelper::print(arr, n);
    SortTestHelper::print(arr2, n);
    SortTestHelper::print(arr3, n);
    SortTestHelper::print(arr4, n);

    delete [] arr;
    delete [] arr2;
    delete [] arr3;
    delete [] arr4;

    return 0;
}

