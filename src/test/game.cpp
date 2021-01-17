#include <cstdint>
#include "testutils.hpp"
#include "../2048/domain/game.hpp"

namespace
{
class GameTestable : public Game
{
public:
    GameTestable(
        Score _win_score, Board::Movable & _board, Player::Movable & _player):
        Game(_win_score, _board, _player)
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
    int      makeSlide_calls = 0;
    Direction makeSlide_out;
    inline Direction makeSlide()
    {
        ++makeSlide_calls;
        return makeSlide_out;
    }
};

class BoardTestable : public Board
{
public:
    inline Position & at(Size _row, Size _column)
    {
        return Board::at(_row, _column);
    }
};
}

TEST_GROUP(GameTest) {};

TEST(GameTest, GenerateRandomNumber)
{
    Board::Movable  board(new Board());
    Player::Movable player(new PlayerTestable());
    GameTestable    game(1, board, player);

    for(int i = 0; i < 100; ++i)
    {
        auto number = game.generateRandomNumber()->value();
        CHECK_TRUE(2 == number || 4 == number);
    }
}

TEST(GameTest, PlaceNumberAfterStart)
{
    Board     *     board = new Board();
    Board::Movable  b(board);
    Player::Movable player(new PlayerTestable());
    GameTestable    game(1, b, player);

    game.start();

    CHECK_EQUAL(1, board->count());
}

TEST(GameTest, QueryPlayerSlideAfterStart)
{
    Board      *     board  = new Board();
    Board::Movable   b(board);
    PlayerTestable * player = new PlayerTestable();
    player->makeSlide_out   = Direction::left;
    Player::Movable  p(player);
    GameTestable     game(1, b, p);

    game.start();

    CHECK_EQUAL(1, player->makeSlide_calls);
}
