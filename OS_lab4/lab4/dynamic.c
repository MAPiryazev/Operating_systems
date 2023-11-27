#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <dlfcn.h>
#include "constants.h"


const char* FIRST_PATH_FOR_LIBRARY = "build/libfirst_lib.so";
const char* SECOND_PATH_FOR_LIBRARY = "build/libsecond_lib.so";
void* descriptor = NULL; //переменная для хранения дескриптора динамически загружаемой библиотеки
int switcher_condition = 2;

float (*Pi)(int accuracy) = NULL;

int*(*Sort)(int * array, int size) = NULL;

void switcher() {
    if(switcher_condition == 1) {

        if(descriptor != NULL){
            dlclose(descriptor);
        }
        descriptor = dlopen(SECOND_PATH_FOR_LIBRARY, RTLD_LAZY);

        Pi = dlsym(descriptor, "Pi");
        Sort = dlsym(descriptor, "Sort");

        switcher_condition = 2;

    } else {

        if(descriptor != NULL){
            dlclose(descriptor);
        }
        descriptor = dlopen(FIRST_PATH_FOR_LIBRARY, RTLD_LAZY);

        Pi = dlsym(descriptor, "Pi");
        Sort = dlsym(descriptor, "Sort");

        switcher_condition = 1;

    }
    printf("Switcher condition changed\n");
}

int main() {
    switcher();
    int received_digit;

    int array[constant_size];
    for (int iteration = 0; iteration < constant_size; iteration++){
        array[iteration] = constant_size - iteration;
    }

    while(scanf("%d", &received_digit) != EOF) {
        if (received_digit == -1){
                dlclose(descriptor);
                return 0;    
        }
        else if (received_digit == 0){
                switcher();
        }
        else if (received_digit == 1){
                int number;
                printf("Enter your accuracy value: ");
                scanf("%d", &number);
                printf("%f\n", (*Pi)(number));
        }
        else if (received_digit == 2){ 
                printf("Sorted array: ");
                Sort(array, constant_size);
                for (int iteration = 0; iteration < constant_size; iteration++){
                    printf("%d, ", array[iteration]);
                }
                printf("\n");
        }
    }
}