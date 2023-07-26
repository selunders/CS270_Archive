// Definition of bubbleSort function

void bubbleSort(int arr[], int len)
{
    printf("Bubble Sorting this array:\n");
    printArr(arr, len);
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
    printf("Sorted:\n");
    printArr(arr, len);
    printf("\n");
}