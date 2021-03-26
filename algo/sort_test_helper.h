
/************************************************
#
#      Filename: sort_test_helper.h
#
#        Author: Sh1Yu6
#   Description: ---
#        Create: 2021-03-22 15:23:56
# Last Modified: 2021-03-22 15:23:56
#***********************************************/

#ifndef __SORT_TEST_HELPER_H
#define __SORT_TEST_HELPER_H

#include <iostream>
#include <string>
#include <cassert>
#include <ctime>
#include <algorithm>
namespace SortTestHelper{
    int* generateRandomArray(int n, int rangLeft, int rangRight){

        assert( rangLeft <= rangRight );
        int* arr = new int[n];
        srand(time(nullptr));
        for( int i = 0; i < n; ++i ){
            arr[i] = rand() % ( rangRight - rangLeft + 1 ) + rangLeft;
        }
        return arr;
    }

    int* generateNearlyOrderedArray(int n, int swapTimes){
        int * arr = new int[n];
        for(int i = 0; i < n; ++i){
            arr[i] = i;
        }
        srand(time(nullptr));
        for(int i = 0; i < swapTimes; ++i){
            int posX = rand() % n;
            int posY = rand() % n;
            std::swap( arr[posX], arr[posY] );
        }
        return arr;
    }

    template<typename T>
    void print(T* arr, int n){
        for(int i = 0; i < n; ++i){
            std::cout << arr[i] << " ";
        }
        std::cout << std::endl;
    }

    template<typename T>
    bool isSorted(T* arr, int n){
        for(int i = 0; i < n - 1; ++i){
            if(arr[i] > arr[i + 1]){
                return false;
            }
        }
        return true;
    }

    template<typename T>
    void testSort( std::string sortName, void(*sort)(T*, int), T* arr, int n){
        clock_t startTime = clock();
        sort(arr, n);
        clock_t endTime = clock();

        assert( isSorted(arr, n) );
        std::cout << sortName << " : " << (double)(endTime - startTime) / CLOCKS_PER_SEC << "s" << std::endl;
    }

    template<typename T>
        int* copyArray(T* a, int n){
            T* arr = new T[n];
            std::copy(a, a + n, arr);
            return arr;
        }
}


#endif //SORT_TEST_HELPER_H
