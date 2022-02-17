#include <stdio.h>
#include <iostream>
#include <stdlib.h>

using namespace std;
 
void swap(int *xp, int *yp)
{
    int temp = *xp;
    *xp = *yp;
    *yp = temp;
}
 
// A function to implement bubble sort
void bubbleSort(int arr[], int n)
{
    int i, j;
    for (i = 0; i < n-1; i++)    
     
    // Last i elements are already in place
    for (j = 0; j < n-i-1; j++)
        if (arr[j] > arr[j+1])
            swap(&arr[j], &arr[j+1]);
}
 
/* Function to print an array */
void printArray(int arr[], int size)
{
    int i;
    for (i=0; i < size; i++)
        printf("%d ", arr[i]);
    printf("\n");
}


int main (int argc, char* argv[]) {
    // if (argc != 2) {
    //     printf("Invalid runner usage! runner requires exactly 1 argument.\n");
    //     return -1;
    // }

    int arrayLength = atoi(argv[1]);
    int arrayToSort[arrayLength];

    for (int i = 0; i < arrayLength; i++) {
        arrayToSort[i] = rand() % 1000;
    }

    bubbleSort(arrayToSort, arrayLength);
    // printf("Sorted array: \n");
    // printArray(arrayToSort, arrayLength);
    return 0;
}