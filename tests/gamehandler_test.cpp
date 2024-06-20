#include "../game/includ/Snake.hpp"
#include "../game/includ/List.hpp"
#include "../game/includ/GameHandler.hpp"
#include <gtest/gtest.h>
#include <stdlib.h>

TEST(GameHandlerTest, IsSnake_Test) {
    Field field{100, 40};
    List<Food> foods;
    List<Snake> snakes;

    Snake s1;

    GameHandler handler{&field, &foods, &snakes};
    handler.AddSnake(&s1);

    EXPECT_FALSE(handler.IsSnake(&s1));

    handler.RemoveSnake(&s1);

    EXPECT_FALSE(handler.IsSnake(&s1));
}


TEST(GameHandlerTest, IsOtherSnake_Test) {
    Field field{100, 40};
    List<Food> foods;
    List<Snake> snakes;

    GameHandler handler{&field, &foods, &snakes};

    Snake s1, *s2;

    EXPECT_FALSE(handler.IsOtherSnake(&s1, &s2));

}
