cmake_minimum_required()
project(unix_learn)

include_directories(include)
AUX_SOURCE_DIRECTORY(lib LIB)

add_executable(10.p6 ${LIB} Chapter-10/p6.c)