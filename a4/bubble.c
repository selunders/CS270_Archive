#include "sort.h"
// Definition of bubbleSort function

void sort(int arr[], int len)
{
    // printf("Bubble Sorting this array:\n");
    // printArr(arr, len);
    while (!(isSorted(arr, len)))
    {
        // printArr(arr, len);
        int i = 0;
        while (i < len - 1)
        {
            if (arr[i] > arr[i + 1])
            {
                swap(&arr[i], &arr[i + 1]);
            }
            i++;
        }
    }
    printf("Sorted: ");
    printArr(arr, len);
}