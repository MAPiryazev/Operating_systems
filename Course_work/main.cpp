#include <iostream>
#include <vector>
#include <chrono>
#include <fstream>
#include "buddy.h"
#include "twon.h"

int main()
{
    buddy_allocator my_buddy_allocator;
    twon my_twon_allocator;

    std::vector<char*> buddy_alloc;
    std::vector<char*> twon_alloc;
    std::vector<std::pair<int,double>> coordinates_buddy;
    std::vector<std::pair<int,double>> coordinates_twon;


    auto start = std::chrono::high_resolution_clock::now();

    for (int i=0; i < 3000; i++){
        buddy_alloc.push_back(my_buddy_allocator.malloc(32));
        auto current_end = std::chrono::high_resolution_clock::now();
        std::chrono::duration<double> duration = current_end - start;
        coordinates_buddy.push_back(std::make_pair(i,duration.count()));

    }
    for (int i=0; i < 3000; i++){
        my_buddy_allocator.free(buddy_alloc[i]);
    }

    auto end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> duration = end - start;
    std::cout << "Время выполнения buddy_allocator " << duration.count() << " секунд" << std::endl;

    auto start1 = std::chrono::high_resolution_clock::now();

    for (int i=0; i < 3000; i++){   
        twon_alloc.push_back(my_twon_allocator.malloc(32));
        auto current_end1 = std::chrono::high_resolution_clock::now();
        std::chrono::duration<double> duration = current_end1 - start1;
        coordinates_twon.push_back(std::make_pair(i, duration.count()));


    }
    for (int i=0; i < 3000; i++){   
        my_twon_allocator.free(twon_alloc[i]);
    }

    auto end1 = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> duration1 = end1 - start1;
    std::cout << "Время выполнения two_n_allocator " << duration1.count() << " секунд" << std::endl;

    // Вывод в файл для coordinates_buddy
    std::ofstream buddy_file("buddy_output.txt");
    if (buddy_file.is_open()) {
        for (int i = 0; i < 3000; i++) {
            buddy_file << coordinates_buddy[i].first << " " << coordinates_buddy[i].second << std::endl;
        }
        buddy_file.close();
    }

    // Вывод в файл для coordinates_twon
    std::ofstream twon_file("twon_output.txt");
    if (twon_file.is_open()) {
        for (int i = 0; i < 3000; i++) {
            twon_file << coordinates_twon[i].first << " " << coordinates_twon[i].second << std::endl;
        }
        twon_file.close();
    }
    
}
