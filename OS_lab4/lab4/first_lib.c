#include "lib.h"

float Pi(int accuracy) { //ряд лейбница
    float pi = 0.0;
    int sign = 1;
    for (int i = 0; i < accuracy; i++) {
        pi += (4.0 / (2 * i + 1)) * sign;
        sign *= -1;
    }
    return pi;
}

int* Sort(int* array, int size) {
    for (int i = 0; i < size-1; i++) {
        for (int j = 0; j < size-i-1; j++) {
            if (array[j] > array[j+1]) {
                int temp = array[j];
                array[j] = array[j+1];
                array[j+1] = temp;
            }
        }
    }
    return array;
}

