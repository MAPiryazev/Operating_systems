#ifndef BUDDY_H
#define BUDDY_H
#include <vector>
#include <algorithm>
#include <math.h>
#include <cstdint>
#include <stdexcept>



struct block{
    unsigned int order;
    char* ptr;
    bool taken = false;
    block(unsigned int o, char* p): order{o}, ptr{p} {}
};

struct buddy_allocator
{  
    const unsigned int SIZE = 1010000; //2^12
    char* memory_ptr;
    std::vector<block*> memory;
    unsigned int get_order(unsigned int);
    
public:
    buddy_allocator();
    char* malloc(unsigned int);
    void free(char* ptr);
    std::vector<block*>::iterator find_buddy(std::vector<block*>::iterator it);
    void merge(std::vector<block*>::iterator it, std::vector<block*>::iterator buddy_allocator);
    ~buddy_allocator();
};

#endif // BUDDY_H
