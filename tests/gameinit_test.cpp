#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include "../game/includ/GameInit.hpp"
#include <cstdlib>
#include <cstdio>

class MockGameInit : public GameInit {
public:
    MockGameInit(int _argc, const char **_argv) : GameInit(_argc, _argv) {}
    MOCK_METHOD(void, WriteHelp, ());
    MOCK_METHOD(bool, HandleArgv, (int argv_idx, int matched_argv, int *num_args, const char **ip));
};

TEST(GameInitTest, HandleArgv_MatchedArgvLessThan4_ValidArg) {
    const char *argv[] = {"program", "1", "2", "3", "4"};
    MockGameInit gameInit(5, argv);
    int num_args[4] = {0};
    const char *ip = nullptr;

    EXPECT_FALSE(gameInit.HandleArgv(0, 0, num_args, &ip));
    EXPECT_EQ(num_args[0], 0);
}

TEST(GameInitTest, HandleArgv_MatchedArgvEqual4) {
    const char *argv[] = {"program", "1", "2", "3", "192.168.0.1"};
    MockGameInit gameInit(5, argv);
    int num_args[4] = {0};
    const char *ip = nullptr;

    EXPECT_FALSE(gameInit.HandleArgv(3, 4, num_args, &ip));
}
