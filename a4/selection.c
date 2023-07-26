#include"sort.h"
// Definition of selectionSort function

void sort(int arr[], int len)
{
    // printf("Selection Sorting this array:\n");
    // printArr(arr, len);

    int i = 0;
    while (i < len - 1)
    {

        int minLocation = i;

        // j will start with the second position in the array
        int j = i + 1;
        while (j < len)
        {
            if (arr[j] < arr[minLocation])
            {
                minLocation = j;
            }
            j++;
        }
        swap(&arr[i], &arr[minLocation]);
        // printArr(arr, len);
        i++;
    }
    printf("Sorted: ");
    printArr(arr, len);
}