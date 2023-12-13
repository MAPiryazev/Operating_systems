#include "twon.h"

twon::twon(){
    memory_ptr = new char[SIZE];
    int size_for_division = SIZE;
    std::vector<buffer> vector_for_1024;
    std::vector<buffer> vector_for_512;
    std::vector<buffer> vector_for_256;
    std::vector<buffer> vector_for_128;
    std::vector<buffer> vector_for_64;
    std::vector<buffer> vector_for_32;

    if (SIZE <= 32) {
        throw std::logic_error("Minimal size of a buffer can`t be less than 32 bytes");
    }
    unsigned int step {0};
    while (size_for_division >= 32){
        if (size_for_division >= 1024){
            vector_for_1024.push_back(buffer(memory_ptr + step));
            size_for_division -= 1024;
            step += 1024;
        }
        if (size_for_division >= 512){
            vector_for_512.push_back(buffer(memory_ptr + step));
            size_for_division -= 512;
            step += 512;
        }
        if (size_for_division >= 256){
            vector_for_256.push_back(buffer(memory_ptr + step));
            size_for_division -= 256;
            step += 256;
        }
        if (size_for_division >= 128){
            vector_for_128.push_back(buffer(memory_ptr + step));
            size_for_division -= 128;
            step += 128;
        }
        if (size_for_division >= 64){
            vector_for_64.push_back(buffer(memory_ptr + step));
            size_for_division -= 64;
            step += 64;
        }
        if (size_for_division >= 32){
            vector_for_32.push_back(buffer(memory_ptr + step));
            size_for_division -= 32;
            step += 32;
        }
    }

    memory.insert(std::make_pair(1024,vector_for_1024));
    memory.insert(std::make_pair(512,vector_for_512));
    memory.insert(std::make_pair(256,vector_for_256));
    memory.insert(std::make_pair(128,vector_for_128));
    memory.insert(std::make_pair(64,vector_for_64));
    memory.insert(std::make_pair(32,vector_for_32));

}

twon::~twon() {
    delete[] memory_ptr;
    for (auto& pair : memory) {
        pair.second.clear();
    }
    memory.clear();
}

unsigned int twon::get_order(unsigned int mem_size){
    unsigned int i = 0;
    while (std::pow(2,i)<(mem_size/sizeof(char))) {
        i++;
    }
    if (i < 5) {
        return 5;
    }
    return i;
}

char* twon::malloc(unsigned int size){
    unsigned int order_of_request = get_order(size);
    
    switch (order_of_request)
    {
    case 5:
        return search(std::round(pow(2, order_of_request)));
        break;
    case 6:
        return search(std::round(pow(2, order_of_request)));
        break;
    case 7:
        return search(std::round(pow(2, order_of_request)));
        break;
    case 8:
        return search(std::round(pow(2, order_of_request)));
        break;
    case 9:
        return search(std::round(pow(2, order_of_request)));
        break;
    case 10:
        return search(std::round(pow(2, order_of_request)));
        break;
    default:
        throw std::invalid_argument("Invalid order. Probably your query is too big");
        break;
    }
    
}

void twon::free(char* ptr) {
    for (auto& pair : memory) {
        for (auto& buf : pair.second) {
            if (buf.ptr == ptr) {
                if (buf.taken == false) {
                    throw std::logic_error("Double freeing of memory");
                }
                buf.taken = false;
                return;
            }
        }
    }
    throw std::invalid_argument("Invalid pointer");
}




inline char *twon::search(int key)
{
    while (key <= 1024){
        auto it = memory.find(key);
        if (it != memory.end() and !it->second.empty()){
            for (int i = 0; i < it->second.size(); i++){
                if (it->second[i].taken == false){
                    it->second[i].taken = true;
                    return it->second[i].ptr;
                }
            }
        }
        key *= 2;
    }
    throw std::runtime_error("Not enough free memory");
}
