#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>
#include <sys/time.h>
#include "constants.h"

struct ThreadArguments {
    int* array;
    int start;
    int end;
};

void Quicksort(int* InputArr, int StartIndex, int EndIndex) {
    if (StartIndex < EndIndex) {
        int pivot = InputArr[EndIndex];
        int i = StartIndex - 1;

        for (int j = StartIndex; j < EndIndex; j++) {
            if (InputArr[j] <= pivot) {
                i++;
                int temp = InputArr[i];
                InputArr[i] = InputArr[j];
                InputArr[j] = temp;
            }
        }

        int temp = InputArr[i + 1];
        InputArr[i + 1] = InputArr[EndIndex];
        InputArr[EndIndex] = temp;

        int partition_index = i + 1;

        Quicksort(InputArr, StartIndex, partition_index - 1);
        Quicksort(InputArr, partition_index + 1, EndIndex);
    }
}

void* thread_function(void* arg) {
    struct ThreadArguments* args = (struct ThreadArguments*)arg;
    Quicksort(args->array, args->start, args->end);
    pthread_exit(NULL); 
}

int main(int argc, char* argv[]){
    if (argc != 2){
        printf("Invalid starting parameters, program was not launched\n");
        return 1;
    }
    int threadsAmount = atoi(argv[1]);
    printf("Amount_of_threads is %d\n", threadsAmount);

    int ArrayForSort[AMOUNT_OF_ELEMENTS];
    int arraySize = sizeof(ArrayForSort) / sizeof(ArrayForSort[0]);
        for (int i = 0; i < arraySize; i++){
            ArrayForSort[i] = AMOUNT_OF_ELEMENTS - i; 
        }

    struct timeval start, end;
    gettimeofday(&start, NULL);    

    pthread_t threads[threadsAmount];
    struct ThreadArguments thread_args[threadsAmount]; 

    int pieceSize = arraySize / threadsAmount;
    int left = arraySize % threadsAmount;

    int startIndex = 0;
    int endIndex = pieceSize - 1;

    for (int iteration = 0; iteration < threadsAmount; iteration++){
        if (left > 0){
            endIndex++;
            left--;
        }

        thread_args[iteration].array = ArrayForSort;
        thread_args[iteration].start = startIndex;
        thread_args[iteration].end = endIndex; 

        pthread_create(&threads[iteration], NULL, thread_function, (void*)&thread_args[iteration]);

        startIndex = endIndex + 1;
        endIndex = startIndex + pieceSize - 1;
    }

    for (int i = 0; i < threadsAmount; i++) {
        pthread_join(threads[i], NULL);
    }

    Quicksort(ArrayForSort,0, arraySize - 1);

    gettimeofday(&end, NULL);
    double execution_time = 
            (end.tv_sec - start.tv_sec)*1000.0;
    execution_time+=
            (end.tv_usec - start.tv_usec)/1000.0;

    printf("Execution_time: %.20f ms\n ", execution_time);   

    // for (int iteration = 0; iteration < arraySize; iteration++){
    //     printf("%d, ", ArrayForSort[iteration]);
    // }
    // printf("\n");

    return 0;
}