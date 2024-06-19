cmake_minimum_required(VERSION 3.13)

set(CMAKE_CXX_STANDARD 17)
set(This game)

include_directories(include)

set(SOURCES
    source/Field.cpp
    source/Food.cpp
    source/GameHandler.cpp
    source/GameInit.cpp
    source/List.cpp
    source/MoveAndPosition.cpp
    source/Point.cpp
    source/Server.cpp
    source/Snake.cpp)

set(HEADERS
    includ/Field.hpp
    includ/Food.hpp
    includ/GameHandler.hpp
    includ/GameInit.hpp
    includ/List.hpp
    includ/MoveAndPosition.hpp
    includ/Point.hpp
    includ/Server.hpp
    includ/Snake.hpp)

add_executable(${This} main.cpp ${SOURCES} ${HEADERS})
