cmake_minimum_required(VERSION 3.29)
project(Doing C)

set(CMAKE_C_STANDARD 11)

find_package(SQLite3 REQUIRED)

include_directories(${SQLite3_INCLUDE_DIRS})

add_executable(Doing src/main.c
        src/crud_functions.c
        src/crud_functions.h)

target_link_libraries(Doing ${SQLite3_LIBRARIES})