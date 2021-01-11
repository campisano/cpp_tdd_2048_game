#include <cstdint>
#include "testutils.hpp"
#include "../2048/domain/game.hpp"

namespace
{
class GameTestable : public Game
{
public:
    GameTestable(Board::Movable & _board): Game(_board, 2048)
    {
    }

    inline Number::Movable generateRandomNumber()
    {
        return Game::generateRandomNumber();
    }
};
}

TEST_GROUP(GameTest) {};

TEST(GameTest, GenerateRandomNumber)
{
    Board::Movable board(new Board());
    GameTestable game(board);

    for(int i = 0; i < 100; ++i)
    {
        auto number = game.generateRandomNumber()->value();
        CHECK_TRUE(2 == number || 4 == number);
    }
}

TEST(GameTest, PlaceNumberAfterStart)
{
    Board * board = new Board();
    Board::Movable b(board);
    GameTestable game(b);

    game.start();

    CHECK_EQUAL(1, board->count());
}
