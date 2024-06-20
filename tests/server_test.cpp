#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <unistd.h>

#include "../game/includ/List.hpp"
#include "../game/includ/Field.hpp"
#include "../game/includ/Server.hpp"

using ::testing::Return;
using ::testing::_;




class EstablishSocket {
    public:
    int establishSock(int domain, int type, int protocol) {
        return socket(domain, type, protocol);
    }
    int setSockOpt(int socket, int level, int option_name, const void *option_value, socklen_t option_len) {
        return setsockopt(socket, level, option_name, &option_name, option_len);
    }
    int bindSocket(int socket, const struct sockaddr* address, socklen_t address_len) {
        return bind(socket, address, address_len);
    }
    int listenSocket(int socket, int backlog) {
        return listen(socket, backlog);
    }

};

class MockEventSelector : public EventSelector {
public:
    MOCK_METHOD(void, Add, (FdHandler * h));
    MOCK_METHOD(void, Remove, (FdHandler * h));
    MOCK_METHOD(void, SetServerFd, (FdHandler * h));
    MOCK_METHOD(void, Run, ());
};

class MockField : public Field {
public:

    MockField(int _size_x, int _size_y) : Field(_size_x, _size_y) {}
    MOCK_METHOD(const char *, GetField, ());


};

class MockGameHandlerGemstone : public GameHandlerGemstone {
public:
    MockGameHandlerGemstone(Field *_field, List<Food> *_foods, List<Snake> *_snakes)
        : GameHandlerGemstone(_field, _foods, _snakes) {}

};


TEST(ServerTest, StartServerWithInvalidSocket_Test) {
    MockEventSelector selector;
    MockField field{100, 40};
    List<Food> foods;
    List<Snake> snakes;
    MockGameHandlerGemstone handler{&field, &foods, &snakes};

    int port = -1;
    const char* ip = "127.0.0.1";

    Server* server = Server::Start(&selector, &field, &handler, 0, port, ip);

    EXPECT_EQ(server, nullptr);
}

TEST(ServerTest, StartServerWithValidSocket_Test) {
    MockEventSelector selector;
    MockField field{100, 40};
    List<Food> foods;
    List<Snake> snakes;
    MockGameHandlerGemstone handler{&field, &foods, &snakes};

    int port = 12345;
    const char* ip = "127.0.0.1";

    Server* server = Server::Start(&selector, &field, &handler, 0, port, ip);

    ASSERT_NE(server, nullptr);
    EXPECT_EQ(server->GetFd(), 4);

    delete server;
}

TEST(ServerTest, StartServerWithNullIP_Test) {
    MockEventSelector selector;
    MockField field{100, 40};
    List<Food> foods;
    List<Snake> snakes;
    MockGameHandlerGemstone handler{&field, &foods, &snakes};

    int port = 12345;
    const char* ip = nullptr;

    Server* server = Server::Start(&selector, &field, &handler, 0, port, ip);

    ASSERT_NE(server, nullptr);
    EXPECT_EQ(server->GetFd(), 4);

    delete server;
}
