#include <iostream>
#include "buddy.h"
#include "twon.h"

int main()
{
    buddy_allocator my_buddy_allocator;

    char *ptr1 = my_buddy_allocator.malloc(64);
    char *ptr2 = my_buddy_allocator.malloc(128);
    
    my_buddy_allocator.free(ptr1);
    my_buddy_allocator.free(ptr2);


    twon my_twon_allocator;

    char *ptr3 = my_twon_allocator.malloc(32);
    char *ptr4 = my_twon_allocator.malloc(64);
    char *ptr5 = my_twon_allocator.malloc(128);
    char *ptr6 = my_twon_allocator.malloc(256);
    char *ptr7 = my_twon_allocator.malloc(321);
    char *ptr8 = my_twon_allocator.malloc(512);
    char *ptr9 = my_twon_allocator.malloc(700);
    my_twon_allocator.free(ptr9);
    


    std::cout << ptr3 << std::endl;
}