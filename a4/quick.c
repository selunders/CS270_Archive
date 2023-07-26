#include"sort.h"

// Definition of selectionSort function
void sort(int arr[], int high){
    quickSort(arr, 0, high-1);
    printf("Sorted: ");
    printArr(arr, high);
}

int partition(int arr[], int low, int high){
    int pivot = arr[high];
    int i = (low -1);
    int j = low;
    while(j < high){
        // printf("i: %i j: %i \nhigh: %i low: %i\n", i,j, arr[high], arr[low]);
        if(arr[j]< pivot){
            i++;
            swap(&arr[i], &arr[j]);
        }
        j++;
    }
    swap(&arr[i+1], &arr[high]);
    return (i+1);
}

void quickSort(int arr[], int low, int high){
    if (low < high){
        int pivotIndex = partition(arr, low, high);
        quickSort(arr, low, pivotIndex-1);
        quickSort(arr, pivotIndex+1, high);
    }
}