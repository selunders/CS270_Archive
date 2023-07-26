// Definition of selectionSort function
int partition(int arr[], int low, int high){
    int pivot = arr[high];
    int i = (low -1);
    int j = low;
    while(j < high-1){
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


// partition (arr[], low, high)
// {
//     // pivot - Element at right most position
//     pivot = arr[high];  
//     i = (low - 1);  // Index of smaller element
//     for (j = low; j <= high-1; j++)
//     {
//         // If current element is smaller than the pivot, swap the element with pivot
//         if (arr[j] < pivot)
//         {
//             i++;    // increment index of smaller element
//             swap(arr[i], arr[j]);
//         }
//     }
//     swap(arr[i + 1], arr[high]);
//     return (i + 1);
// }
// Reference Pseudocode:
// Quick Sort

// /**
// * The main function that implements quick sort.
// * @Parameters: array, starting index and ending index
// */
// quickSort(arr[], low, high)
// {
//     if (low < high)
//     {
//         // pivot_index is partitioning index, arr[pivot_index] is now at correct place in sorted array
//         pivot_index = partition(arr, low, high);

//         quickSort(arr, low, pivot_index - 1);  // Before pivot_index
//         quickSort(arr, pivot_index + 1, high); // After pivot_index
//     }
// }
// Partition Method

// /**
// * The function selects the last element as pivot element, places that pivot element correctly in the array in such a way
// * that all the elements to the left of the pivot are lesser than the pivot and
// * all the elements to the right of pivot are greater than it.
// * @Parameters: array, starting index and ending index
// * @Returns: index of pivot element after placing it correctly in sorted array
// */