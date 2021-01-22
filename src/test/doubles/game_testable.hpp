#ifndef GAME_TESTABLE__HPP__
#define GAME_TESTABLE__HPP__

#include "../../2048/domain/game.hpp"

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

#endif
