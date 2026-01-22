#include <iostream>
using namespace std; 

void swap(int &a, int &b){
    int temp = a; 
    a = b; 
    b = temp;
}

void selectionSort(int arr[], int size){
    for (int i = 0; i<size-1; i++){
        int imin = i; 
        for(int j = i + 1; j<size; j++){
            if (arr[imin] > arr[j]){
                imin = j;
            }
        }
        swap(arr[imin], arr[i]);
    }
}

