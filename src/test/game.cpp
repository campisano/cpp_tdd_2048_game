#include <cstdint>
#include "testutils.hpp"
#include "../2048/domain/game.hpp"

namespace
{
class GameTestable : public Game
{
public:
    GameTestable(Board::Movable & _board, Player::Movable & _player): Game(2048,
                _board, _player)
    {
    }

    inline Number::Movable generateRandomNumber()
    {
        return Game::generateRandomNumber();
    }
};

class PlayerTestable : public Player
{
public:
    bool makeSlide_in;
    Direction makeSlide_out;
    inline Direction makeSlide()
    {
        makeSlide_in = true;
        return makeSlide_out;
    }
};
}

TEST_GROUP(GameTest) {};

TEST(GameTest, GenerateRandomNumber)
{
    Board::Movable board(new Board());
    Player::Movable player(new PlayerTestable());
    GameTestable game(board, player);

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
    Player::Movable player(new PlayerTestable());
    GameTestable game(b, player);

    game.start();

    CHECK_EQUAL(1, board->count());
}

TEST(GameTest, QueryPlayerSlideAfterStart)
{
    Board * board = new Board();
    Board::Movable b(board);
    PlayerTestable * player = new PlayerTestable();
    player->makeSlide_out = Direction::left;
    Player::Movable p(player);
    GameTestable game(b, p);

    game.start();

    CHECK_EQUAL(true, player->makeSlide_in);
}
