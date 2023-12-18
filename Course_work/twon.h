#ifndef TWON_H
#define TWON_H
#include <vector>
#include <map>
#include <stdexcept>
#include <math.h>
#include <iostream>
#include "consts.h"


struct buffer{
    char* ptr;
    bool taken = false;
    buffer(char* p):  ptr{p} {}
};

class twon{
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
