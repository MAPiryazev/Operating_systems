#ifndef TWON_H
#define TWON_H
#include <vector>
#include <map>
#include <stdexcept>
#include <math.h>
#include <iostream>



struct buffer{
    char* ptr;
    bool taken = false;
    buffer(char* p):  ptr{p} {}
};

class twon{
    const unsigned int SIZE = 1<<12; //2^12
    char* memory_ptr;
    std::map<int,std::vector<buffer>> memory;
public:
    twon();
    unsigned int get_order(unsigned int);
    char* malloc(unsigned int);
    void free(char* ptr);

    inline char* search(int key);

    ~twon();
};

#endif // TWON_H
