#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <fcntl.h>
#include <semaphore.h>
#include <sys/mman.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <ctype.h>

const int MAX_STRING_SIZE = 200;

int get_semaphore_value(sem_t* semaphore)
{
    int value;
    sem_getvalue(semaphore, &value);
    return value;
}

void set_semaphore_value(sem_t* semaphore, int value)
{
    while (get_semaphore_value(semaphore) < value)
    {
        sem_post(semaphore);
    }
    while (get_semaphore_value(semaphore) > value)
    {
        sem_wait(semaphore);
    }
}

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
    input[length] = '\0';
    return input;
}

int main(int argc, char *argv[])
{
    char* semaphore_name = argv[0];
    char* mmap_filename = argv[1];
    int mmap_file;
    
    sem_t* semaphore = sem_open(semaphore_name, O_RDWR | O_CREAT, 0777);
    
    int flag = 1;
    
    while(flag)
    {
        while(get_semaphore_value(semaphore) == 2)
        {
            continue;
        }

        mmap_file = shm_open(mmap_filename, O_RDWR | O_CREAT, 0777);
        error_checking(mmap_file, "File open error");

        struct stat buffer;
        fstat(mmap_file, &buffer);
        int size = buffer.st_size;
        
        char* map = (char*) mmap(NULL, size, PROT_READ | PROT_WRITE, MAP_SHARED, mmap_file, 0);
        char input_string[MAX_STRING_SIZE];
        char input_string_size = 0;
        for (int index = 0; index < size; ++index)
        {
            char symbol = map[index];
            
            if (symbol == '\n')
            {
                char* new_string;
                new_string = reverseString (input_string);
                write(fileno(stdout), new_string, sizeof(char) * strlen(new_string));
                write(fileno(stdout), "\n", sizeof(char));
                input_string_size = 0;
                continue;
            }
            
            input_string[input_string_size] = map[index];
            ++input_string_size;
        }
        sem_unlink(semaphore_name);
        munmap(map, size);
        close(mmap_file);
        flag = 0;
    }
    
    return 0;
}