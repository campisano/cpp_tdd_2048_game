#include <cstdint>
#include "testutils.hpp"
#include "../2048/domain/game.hpp"

namespace
{
class GameTestable : public Game
{
public:
    inline Number::Movable generateRandomNumber()
    {
        return Game::generateRandomNumber();
    }
};
}

TEST_GROUP(GameTest) {};

TEST(GameTest, GenerateRandomNumber)
{
    GameTestable game;

    for(int i = 0; i < 100; ++i)
    {
        auto number = game.generateRandomNumber()->value();
        CHECK_TRUE(2 == number || 4 == number);
    }
}
