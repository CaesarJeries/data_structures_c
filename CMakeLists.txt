cmake_minimum_required(VERSION 3.18.4)

# specify that the project is implemented in pure C
project(data_structures C)

file(GLOB SRC_FILES ./src/*.c)
file(GLOB HEADER_FILES ./include/*.h)

add_library(data_structures SHARED ${SRC_FILES})

target_include_directories(data_structures PUBLIC "./include")
