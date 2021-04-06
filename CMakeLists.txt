cmake_minimum_required(VERSION 3.18.4)

# specify that the project is implemented in pure C
project(data_structures C)

add_library(data_structures SHARED
    ./src/linked_list.c
)

target_include_directories(data_structures PUBLIC "./include")
