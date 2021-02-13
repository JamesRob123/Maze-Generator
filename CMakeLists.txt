cmake_minimum_required(VERSION 3.16.3)
project(MyProject VERSION 1.0.0)

SET(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Wall -Werror -Wextra -std=gnu17 -s -O2")

add_executable(generate_maze generate_maze.c cell.c maze.c bmp.c helper.c array_list.c)

target_link_libraries(generate_maze PRIVATE m)