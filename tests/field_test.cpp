#include "../game/includ/Field.hpp"
#include <gtest/gtest.h>

TEST(FieldTest, get_xy__Test) {
    Field field {150, 200};
    EXPECT_EQ(field.GetSizeX(), 150);
    EXPECT_EQ(field.GetSizeY(), 200);
}

TEST(FieldTest, get_minus_xy__Test) {
    Field field {-10, -10};
    EXPECT_EQ(field.GetSizeX(), 0);
    EXPECT_EQ(field.GetSizeY(), 0);
}

TEST(FieldTest, get_zero_xy__Test) {
    Field field {0, 0};
    EXPECT_EQ(field.GetSizeX(), 0);
    EXPECT_EQ(field.GetSizeY(), 0);
}
