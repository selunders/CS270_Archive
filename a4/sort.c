// ----------------------------
// Sorting Function Definitions
// ----------------------------
#include"sort.h"
// Prints out an array

void printArr(int arr[], int len){
    int i = 0;
    printf("[ ");
    while(i < len){
        printf("%i ", arr[i++]);
    }
    printf("]\n");
}

// Checks if an array is sorted

int isSorted(int arr[], int len){
    int i = 0;
    while(i < len-1){
        if(arr[i] > arr[i+1]){
            return 0;
        }
        i++;
    }
    return 1;
}

// Make a copy of an array
// (Then you can sort the duplicate array while preserving the original)

void arrDup( int orig[], int cpy[], int len){
    // printf("Filling temporary array...\n");
    int i = 0;
    while(i < len){
        cpy[i] = orig[i];
        i++;
    }
}

// Swaps two integers in an array

void swap(int* a, int* b){
    int temp = *a;
    *a = *b;
    *b = temp;
}