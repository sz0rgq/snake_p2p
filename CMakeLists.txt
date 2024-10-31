cmake_minimum_required(VERSION 3.13)

project(snake_tcp)

set(This temporary_snake_tcp)
set(CMAKE_C_STANDARD 17)
set(CMAKE_CXX_STANDARD 17)

add_subdirectory(game)
enable_testing()

add_subdirectory(googletest)
add_subdirectory(tests)


#newline
