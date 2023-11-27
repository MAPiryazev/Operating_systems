 #include "lib.h"
 #include "constants.h"

int main() {
    int received_digit;

    int array[constant_size];
    for (int iteration = 0; iteration < constant_size; iteration++){
        array[iteration] = constant_size - iteration;
    }

    while(scanf("%d", &received_digit) != EOF) {
        if (received_digit == -1){
                return 0;    
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