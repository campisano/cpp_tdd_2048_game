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
    int       makeSlide_calls = 0;
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

void fillBoardWithUnmergeableNumbers(
    BoardTestable & _board, int _numbers, int _value);
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

TEST(GameTest, GameEndWhenWin)
{
    BoardTestable  * board  = new BoardTestable();
    auto             n1     = Number::make(1024);
    board->at(2, 0).place(n1);
    auto             n2     = Number::make(1024);
    board->at(2, 1).place(n2);
    PlayerTestable * player = new PlayerTestable();
    player->makeSlide_out   = Direction::left;
    Board::Movable   b(board);
    Player::Movable  p(player);
    GameTestable     game(2048, b, p);

    game.start();

    CHECK_EQUAL(true,  game.playerWin());
    CHECK_EQUAL(false, game.playerLose());
    CHECK_EQUAL(1, player->makeSlide_calls);
}

TEST(GameTest, GameEndWhenLose)
{
    BoardTestable  * board = new BoardTestable();
    fillBoardWithUnmergeableNumbers(*board, board->size() - 1, 16);
    PlayerTestable * player = new PlayerTestable();
    player->makeSlide_out   = Direction::left;
    Board::Movable   b(board);
    Player::Movable  p(player);
    GameTestable     game(2048, b, p);

    game.start();

    CHECK_EQUAL(true,  game.playerLose());
    CHECK_EQUAL(false, game.playerWin());
    CHECK_EQUAL(1, player->makeSlide_calls);
}

namespace
{
// TODO duplicated
void fillBoardWithUnmergeableNumbers(
    BoardTestable & _board, int _numbers, int _value)
{
    Position * p = & _board.at(0, 0);
    bool forward = true;
    for(int i = 0; i < _numbers; ++i)
    {
        auto n = Number::make(_value * (1 + (i % 2)));
        p->place(n);
        if(forward)
        {
            if(p->hasRight())
            {
                p = & p->right();
            }
            else if(p->hasDown())
            {
                forward = false;
                p = & p->down();
            }
        }
        else
        {
            if(p->hasLeft())
            {
                p = & p->left();
            }
            else if(p->hasDown())
            {
                forward = true;
                p = & p->down();
            }
        }
    }
}
}
