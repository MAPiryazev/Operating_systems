#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <fcntl.h>

void error_check(int received, char* output){ 
    if (received == -1){
        printf("%s\n", output);
        exit(-1);
    }
}

char* pull_string_from_file() {
    int received_length = 0;
    int capacity = 1;
    char* string_for_output = (char*) malloc(sizeof(char));
    char input_symbol = getchar();

    if (input_symbol == EOF) {
        return NULL;
    }
    if (input_symbol == '\n') {
        input_symbol = getchar();
    }

    while (input_symbol != '\n') {
        if (received_length >= capacity) {
            capacity *= 2;
            string_for_output = (char*) realloc(string_for_output, capacity * sizeof(char));
        }

        string_for_output[received_length] = input_symbol;
        ++received_length;
        input_symbol = getchar();
    }

    string_for_output[received_length] = '\0';
    return string_for_output;
}

int main(){
    int pipe1_fd[2];
    int pipe2_fd[2];
    error_check(pipe(pipe1_fd), "An error occured while creating pipe №1");
    error_check(pipe(pipe2_fd), "An error occured while creating pipe №2");
    
    char* file_id_1 = pull_string_from_file(); 
    char* file_id_2 = pull_string_from_file();
    int output_file_first, output_file_second;
    error_check(output_file_first = open(file_id_1, O_RDWR | O_CREAT, 0777), "File №1 was not opened due to unexpected error");
    error_check(output_file_second = open(file_id_2, O_RDWR | O_CREAT, 0777), "File №2 was not opened due to unexpected error");

    pid_t first_process_id = fork();
    error_check(first_process_id, "Error while creating a process");
    if (first_process_id == 0){
        printf("First child process started successfully\n"); 
        close(pipe1_fd[1]); 
        close(pipe2_fd[0]); 
        close(pipe2_fd[1]); 
        error_check(dup2(pipe1_fd[0], fileno(stdin)), "dup2 error");
        close(pipe1_fd[0]); 
        error_check(dup2(output_file_first, fileno(stdout)), "dup2 error"); 
        close(output_file_first); 
        char* const* argv = NULL; 
        error_check(execv("child.out", argv), "Execv error");
    } else {
        pid_t second_process_id = fork();
        error_check(second_process_id, "Error while creating a process");
        if (second_process_id == 0){
            printf("Second child process started successfully\n"); 
            close(pipe2_fd[1]); 
            close(pipe1_fd[0]); 
            close(pipe1_fd[1]); 
            error_check(dup2(pipe2_fd[0], fileno(stdin)), "dup2 error"); 
            close(pipe2_fd[0]); 
            error_check(dup2(output_file_second, fileno(stdout)), "dup2 error"); 
            close(output_file_second); 
            char* const* argv = NULL; 
            error_check(execv("child.out", argv), "Execv error");
        } else {
            printf("Parent process started successfully\n"); 
            close(pipe1_fd[0]); 
            close(pipe2_fd[0]); 
            char* string_from_file; 
            int string_sequence_number;
            while ((string_from_file = pull_string_from_file()) != NULL) 
            { 
                int string_length = strlen(string_from_file) + 1;  
                if (!(string_sequence_number % 2 == 0)) 
                { 
                    write(pipe1_fd[1], &string_length, sizeof(int)); 
                    write(pipe1_fd[1], string_from_file, sizeof(char) * string_length); 
                } 
                else 
                { 
                    write(pipe2_fd[1], &string_length, sizeof(int)); 
                    write(pipe2_fd[1], string_from_file, sizeof(char) * string_length); 
                } 
                string_sequence_number++;
            } 
            close(pipe1_fd[1]); 
            close(pipe2_fd[1]); 
            close(output_file_first); 
            close(output_file_second);
        }
    }
    return 0;
}