#include <cstdint>
#include "testutils.hpp"
#include "../2048/domain/game.hpp"

#include <cmath>
#include <iostream>

namespace
{
class GameTestable : public Game
{
public:
    GameTestable(
        Score               _win_score,
        Board::Movable   &  _board,
        Player::Movable  &  _player,
        Observer::Movable & _observer):
        Game(_win_score, _board, _player, _observer)
    {
    }

    void turn()
    {
        Game::turn();
    }

    Number::Movable generateRandomNumber()
    {
        return Game::generateRandomNumber();
    }
};

class BoardTestable : public Board
{
public:
    void fill(std::vector<std::vector<Number::Value>> _numbers)
    {
        Position * p_row = & at(0, 0);
        Position * p_col = p_row;

        for(auto row = _numbers.begin(); row != _numbers.end(); ++row)
        {
            for(auto col = row->begin(); col != row->end(); ++col)
            {
                if((*col) != 0)
                {
                    auto n = Number::make(*col);
                    p_col->place(n);
                }

                if(p_col->hasRight())
                {
                    p_col = & p_col->right();
                }
            }

            if(p_row->hasDown())
            {
                p_row = & p_row->down();
                p_col = p_row;
            }
        }
    }
};

class PlayerTestable : public Player
{
public:
    int       chooseDirection_calls = 0;
    Direction chooseDirection_out;
    Direction chooseDirection()
    {
        ++chooseDirection_calls;
        return chooseDirection_out;
    }
};

class ObserverTestable : public Observer
{
public:
    void notifyStart(Board::Array) {}
    void notifyNumberPlaced(Number::Value, Board::Array) {}
    void notifySlide(Direction, Board::Array) {}
    void notifyEnd(bool, Score) {}
};
}

TEST_GROUP(GameTest) {};

TEST(GameTest, GenerateRandomNumber)
{
    Board::Movable    board(new Board());
    Player::Movable   player(new PlayerTestable());
    Observer::Movable observer(new ObserverTestable());
    GameTestable      game(1, board, player, observer);

    for(int i = 0; i < 100; ++i)
    {
        auto number = game.generateRandomNumber()->value();
        CHECK_TRUE(2 == number || 4 == number);
    }
}

TEST(GameTest, PlaceNumberAfterStart)
{
    Board      *      board = new Board();
    Board::Movable    b(board);
    Player::Movable   player(new PlayerTestable());
    Observer::Movable observer(new ObserverTestable());
    GameTestable      game(1, b, player, observer);

    game.start();

    CHECK_EQUAL(1, board->count());
}

TEST(GameTest, QueryPlayerSlideAfterStart)
{
    BoardTestable  *  board = new BoardTestable();
    board->fill(
    {
        { 8, 8, 0, 0 },
        { 0, 0, 0, 0 },
        { 0, 0, 0, 0 },
        { 0, 0, 0, 0 }
    });
    Board::Movable    b(board);
    PlayerTestable  * player = new PlayerTestable();
    player->chooseDirection_out = Direction::left;
    Player::Movable   p(player);
    Observer::Movable observer(new ObserverTestable());
    GameTestable      game(16, b, p, observer);

    game.start();

    CHECK_EQUAL(1, player->chooseDirection_calls);
}

TEST(GameTest, GameEndWhenWin)
{
    BoardTestable  *  board  = new BoardTestable();
    board->fill(
    {
        {    0,    0, 0, 0 },
        {    0,    0, 0, 0 },
        { 1024, 1024, 0, 0 },
        {    0,    0, 0, 0 }
    });
    PlayerTestable  * player = new PlayerTestable();
    player->chooseDirection_out = Direction::left;
    Board::Movable    b(board);
    Player::Movable   p(player);
    Observer::Movable observer(new ObserverTestable());
    GameTestable      game(2048, b, p, observer);

    game.turn();

    CHECK_EQUAL(true,  game.playerWin());
    CHECK_EQUAL(false, game.playerLose());
    CHECK_EQUAL(1, player->chooseDirection_calls);
}

TEST(GameTest, GameEndWhenLose)
{
    BoardTestable  *  board = new BoardTestable();
    board->fill(
    {
        { 16, 32, 16, 32 },
        { 32, 16, 32, 16 },
        { 16, 32, 16, 32 },
        {  0, 32, 16, 32 }
    });
    PlayerTestable  * player = new PlayerTestable();
    player->chooseDirection_out = Direction::left;
    Board::Movable    b(board);
    Player::Movable   p(player);
    Observer::Movable observer(new ObserverTestable());
    GameTestable      game(2048, b, p, observer);

    game.turn();

    CHECK_EQUAL(true,  game.playerLose());
    CHECK_EQUAL(false, game.playerWin());
    CHECK_EQUAL(1, player->chooseDirection_calls);
}
