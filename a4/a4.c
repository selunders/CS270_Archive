/* a1.c
 *
 * CS 270.Rinker.........Seth Lunders
 * 2/1/2021..............lund4272@vandals.uidaho.edu
 *
 * This program sorts an array of integers using three methods: bubble sort, selection sort, and quicksort.
 * 
 * 
 *-------------------------------------------------------------------------------------
 */

#include "sort.h"
#include "sort.c"
// #include "bubble.c"
// #include "selection.c"
// #include "quick.c"

// create an array

// int intarr[8] = {37, 476, 8, 43, 97, 2, 12, 3};
int intarr[8] = {4,3,2,1,5,6,1,7};
int arrCopy[8];
int size = (sizeof intarr / sizeof intarr[0]);

// int intarr[8] = {1,2,3,4,5,6,7,8};

int main()
{
    // output the original array
    printf("Sorting the array:");
    printArr(intarr, size);
    // Copy original into temporary array
    arrDup(intarr, arrCopy, size);
    sort(arrCopy, size);


    // Bubblesort
    // Reset temporary array
    // arrDup(intarr, arrCopy, size);

    // Selection sort
    // selectionSort(arrCopy, size);
    // Reset temporary array
    // arrDup(intarr, arrCopy, size);

    // Print out sorting message, then quicksort
    // printf("Quick Sorting this array:\n");
    // printArr(arrCopy, size);
    // quickSort(arrCopy, 0, size);
    // Print sorted Array
    // printf("Sorted:\n");
    // printArr(arrCopy, size);
}