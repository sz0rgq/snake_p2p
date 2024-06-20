#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include "field_test.cpp"
#include "point_test.cpp"
#include "snake_test.cpp"
#include "server_test.cpp"
#include "gamehandler_test.cpp"
#include "gameinit_test.cpp"

int main(int argc, char **argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
