#include "lib.h"

float Pi(int accuracy) //формлуа Валлиса
{
    float pi = 2.0;
    for (int i = 1; i <= accuracy; i++) {
        pi *= (4.0 * i * i) / ((4.0 * i * i) - 1);
    }
    return pi;
}

void swap(int* a, int* b) {
    int t = *a;
    *a = *b;
    *b = t;
}
int partition(int arr[], int low, int high) {
    int pivot = arr[high];
    int i = (low - 1);

    for (int j = low; j <= high - 1; j++) {
        if (arr[j] < pivot) {
            i++;
            swap(&arr[i], &arr[j]);
        }
    }
    swap(&arr[i + 1], &arr[high]);
    return (i + 1);
}
void quickSort(int arr[], int low, int high) {
    if (low < high) {
        int pi = partition(arr, low, high);
        quickSort(arr, low, pi - 1);
        quickSort(arr, pi + 1, high);
    }
}
int* Sort(int* array, int size) {
    quickSort(array, 0, size - 1);
    return array;
}


