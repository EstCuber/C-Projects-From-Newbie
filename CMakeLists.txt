cmake_minimum_required(VERSION 3.10)

project(C-Projects-From-Newbie C)

set(CMAKE_C_STANDARD 11)
set(CMAKE_C_STANDARD_REQUIRED ON)

include_directories(${CMAKE_SOURCE_DIR})
add_executable(test
    libs/allocators/allocator_with_list/allocator.c
    tests/allocators/allocator_test.c
)
