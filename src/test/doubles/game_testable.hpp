#ifndef GAME_TESTABLE__HPP__
#define GAME_TESTABLE__HPP__

#include "../../2048/domain/game.hpp"

class GameTestable : public Game
{
public:
    GameTestable(
        Score            _win_score,
        Board::Movable & _board,
        Player     &     _player,
        Observer    &    _observer):
        Game(_win_score, _board, _player, _observer)
    {
    }

    bool  playerWin()   const
    {
        return Game::playerWin();
    }

    bool  playerLose()  const
    {
        return Game::playerLose();
    }

    void turn()
    {
        Game::turn();
    }

    Number::Movable generateRandomNumber() const
    {
        return Game::generateRandomNumber();
    }
};

#endif
