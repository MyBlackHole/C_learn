cmake_minimum_required(VERSION 3.0)

project(versionsymbol C CXX)

set(A_SRCS "")

include_directories("${PROJECT_SOURCE_DIR}/liba/")

file(GLOB_RECURSE  A_SRCS ${PROJECT_SOURCE_DIR}/liba/*.c)
file(GLOB_RECURSE  A_LDS ${PROJECT_SOURCE_DIR}/liba/a.lds)
message(${A_LDS})
add_library(a SHARED ${A_SRCS})
target_link_libraries(a "-Wl,--version-script=${A_LDS}")


set(MAIN_SRCS "")
file(GLOB_RECURSE  MAIN_SRCS ${PROJECT_SOURCE_DIR}/main.c)
add_executable(main ${MAIN_SRCS})
target_link_libraries(main a)
