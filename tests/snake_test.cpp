#include "../game/includ/Snake.hpp"
#include "../game/includ/GameHandler.hpp"
#include "../game/includ/MoveAndPosition.hpp"
#include <gtest/gtest.h>


TEST(SnakeClass, getLen_Test) {
    Snake *snake = new (Snake);
    EXPECT_EQ(snake->GetLen(), 1);
}

TEST(SnakeClass, changeDirection_Test) {
    Snake snake;
    MoveVector mv {2, 2};
    snake.ChangeDirection(&mv);
    EXPECT_EQ(snake.GetMove().GetX(), 2);
    EXPECT_EQ(snake.GetMove().GetY(), 2);
}

TEST(SnakeClass, Move_Test) {
    Snake snake;
    snake.Move();
    EXPECT_EQ(snake.GetMove().GetX(), 0);
}
