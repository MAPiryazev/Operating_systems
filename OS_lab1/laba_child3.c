#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <ctype.h>

void error_checking(int result, char* error)
{
    if (result == -1)
    {
        printf("%s\n", error);
        exit(-1);
    }
}

char* reverseString(char* input) {
    int length = strlen(input);
    int first_marker = 0;
    int last_marker = length - 1;

    while (first_marker < last_marker) {
        char temp = input[first_marker];
        input[first_marker] = input[last_marker];
        input[last_marker] = temp;
        first_marker++;
        last_marker--;
    }
    return input;
}


int main()
{

    int input_size;
    while (read(fileno(stdin), &input_size, sizeof(int)) != 0)// Тут чтение из стандартного потока пока в нем что-то есть?
    {
        char input_string[input_size];
        read(fileno(stdin), &input_string, sizeof(char) * input_size);
        char* result_string;
        result_string = reverseString(input_string);
        write(fileno(stdout), result_string, sizeof(char) * strlen(result_string));
        write(fileno(stdout), "\n", sizeof(char));
    }
    
    return 0;
}
