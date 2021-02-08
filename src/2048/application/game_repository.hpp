#ifndef GAME_REPOSITORY__HPP__
#define GAME_REPOSITORY__HPP__

#include "../domain/board.hpp"
#include "../domain/game.hpp"
#include "../domain/observer.hpp"
#include "../domain/player.hpp"
#include "../domain/score.hpp"

class GameRepository
{
public:
    Game::Movable create(
        Score      &     _win_score,
        Board::Movable & _board,
        Player     &     _player,
        Observer    &    _observer);
};

#endif
