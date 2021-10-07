cmake_minimum_required(VERSION 3.16)
project(Redis_Code C)

set(CMAKE_C_STANDARD 11)

include_directories(include/adlist_test)

add_executable(list wrapper/zmalloc.c struct/adlist.c test/struct_test/adlist_test.c)
