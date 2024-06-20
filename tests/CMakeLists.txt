cmake_minimum_required(VERSION 3.13)
set(CMAKE_CXX_STANDARD 17)

set(SOURCES
    ../game/source/Field.cpp
    ../game/source/Food.cpp
    ../game/source/GameHandler.cpp
    ../game/source/GameInit.cpp
    ../game/source/List.cpp
    ../game/source/MoveAndPosition.cpp
    ../game/source/Point.cpp
    ../game/source/Server.cpp
    ../game/source/Snake.cpp)


add_executable(main_test main_test.cpp ${SOURCES})
add_executable(point_test point_test.cpp ${SOURCES})
add_executable(field_test field_test.cpp ${SOURCES})
add_executable(snake_test snake_test.cpp ${SOURCES})
add_executable(server_test server_test.cpp ${SOURCES})
add_executable(gamehandler_test gamehandler_test.cpp ${SOURCES})
add_executable(gameinit_test gameinit_test.cpp ${SOURCES})

target_link_libraries(main_test gtest gtest_main gmock_main)
target_link_libraries(point_test gtest_main)
target_link_libraries(field_test gtest_main)
target_link_libraries(snake_test gtest_main)
target_link_libraries(server_test gtest_main gmock_main)
target_link_libraries(gamehandler_test gtest_main)
target_link_libraries(gameinit_test gtest_main gmock_main)

add_test(NAME main_test COMMAND main_test)
add_test(NAME point_test COMMAND point_test)
add_test(NAME field_test COMMAND field_test)
add_test(NAME snake_test COMMAND field_test)
add_test(NAME server_test COMMAND server_test)
add_test(NAME gamehandler_test COMMAND gamehandler_test)
add_test(NAME gameinit_test COMMAND gameinit_test)
