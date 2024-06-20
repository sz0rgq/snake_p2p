#include "../game/includ/Point.hpp"
#include <gtest/gtest.h>

TEST(PointClass, get_xy_Test) {
    Point point {5, 10};
    EXPECT_EQ(point.GetX(), 5);
    EXPECT_EQ(point.GetY(), 10);
}

TEST(PointClass, get_minus_xy_Test) {
    Point point {-1, -1};
    EXPECT_EQ(point.GetX(), 0);
    EXPECT_EQ(point.GetY(), 0);
}


TEST(PointClass, set_xy_Test) {
    Point point {4, 6};
    point.SetX(3);
    point.SetY(7);
    EXPECT_EQ(point.GetX(), 3);
    EXPECT_EQ(point.GetY(), 7);
}

TEST(PointClass, set_minus_xy_Test) {
    Point point {4, 6};
    point.SetX(-3);
    point.SetY(-7);
    EXPECT_EQ(point.GetX(), 4);
    EXPECT_EQ(point.GetY(), 6);
}
