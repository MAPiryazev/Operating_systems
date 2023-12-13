cmake_minimum_required(VERSION 3.5)

project(buddy LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(buddy twon main.cpp buddy.cpp twon.cpp)

install(TARGETS buddy
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)

