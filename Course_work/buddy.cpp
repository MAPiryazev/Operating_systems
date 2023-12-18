#include "buddy.h"
#include "consts.h"

unsigned int buddy_allocator::get_order(unsigned int mem_size){
    unsigned int i = 0;
    while (std::pow(2,i)<(mem_size/sizeof(char))) {
        i++;
    }
    return i;
}

buddy_allocator::buddy_allocator(){
    memory_ptr = new char[SIZE];
    memory.push_back(new block(get_order(SIZE),memory_ptr));
}

char *buddy_allocator::malloc(unsigned int size){
    unsigned int order_of_request = get_order(size);
    bool found_block_of_correct_order = false;

    if(((1<<order_of_request)+total_allocated)>SIZE){
        throw std::runtime_error("not enough memory");
    }
    bool blocks_available = false;
    total_allocated+=(1<<order_of_request);
    while (!found_block_of_correct_order) {
        for(auto b: memory){
            if(b->taken) continue;
            if(b->order == order_of_request){
                found_block_of_correct_order = true;
                b->taken = true;
                return b->ptr;
            }
        }
        for(auto b: memory){
            if(b->taken) continue;
            if(b->order > order_of_request){
                b->order--;
                memory.insert(std::find(memory.begin(),memory.end(),b)+1,new block(b->order,b->ptr+std::lround(std::pow(2,b->order))));
                blocks_available = true;
                break;
            }
        }
        if (!(blocks_available || found_block_of_correct_order)) throw std::runtime_error("no space left in allocator");
    }
    return nullptr;
}

void buddy_allocator::free(char *ptr) {
    for (auto it = memory.begin(); it != memory.end(); ++it) {
        if ((*it)->ptr == ptr && (*it)->taken) {
            total_allocated-=(1<<(*it)->order);
            (*it)->taken = false;
            auto buddy_allocator = find_buddy(it);
            while (buddy_allocator != memory.end() && !(*buddy_allocator)->taken) {
                merge(it, buddy_allocator);
                buddy_allocator = find_buddy(it);
            }
            break;
        }
    }

}

std::vector<block*>::iterator buddy_allocator::find_buddy(std::vector<block*>::iterator it) {
    uintptr_t buddy_address = ((uintptr_t)(*it)->ptr ^ (1 << (*it)->order));
    for (auto buddy_allocator = memory.begin(); buddy_allocator != memory.end(); ++buddy_allocator) {
        if ((uintptr_t)(*buddy_allocator)->ptr == buddy_address && (*buddy_allocator)->order == (*it)->order) {
            return buddy_allocator;
        }
    }
    return memory.end();
}

void buddy_allocator::merge(std::vector<block*>::iterator it, std::vector<block*>::iterator buddy_allocator) {
    if ((*it)->ptr > (*buddy_allocator)->ptr) {
        std::swap(it, buddy_allocator);
    }
    (*it)->order++;
    delete *buddy_allocator;
    memory.erase(buddy_allocator);
}

buddy_allocator::~buddy_allocator() {
    delete[] memory_ptr;
    for(auto b: memory){
        delete b;
    }
    memory.clear();
}
