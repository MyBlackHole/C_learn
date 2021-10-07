cmake_minimum_required(VERSION 3.16)
project(crypto_algorithms C)

set(CMAKE_C_STANDARD 11)

include_directories(.)

add_executable(aes aes.c aes_test.c)
