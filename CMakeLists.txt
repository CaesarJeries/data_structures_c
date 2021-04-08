cmake_minimum_required(VERSION 3.18.4)
set(CMAKE_C_STANDARD 99)

# specify that the project is implemented in pure C
project(data_structures C)

add_library(data_structures SHARED
    ./src/linked_list.c
)

target_include_directories(data_structures PUBLIC "./include")

set(TEST_LIBS check pthread rt subunit m)

add_executable(linked_list_test ./test/linked_list_test.c)
target_include_directories(linked_list_test PUBLIC "./include")
target_link_libraries(linked_list_test ${TEST_LIBS} data_structures)

add_test(data_structures linked_list_test)
