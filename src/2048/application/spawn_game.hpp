#ifndef SPAWN_GAME__HPP__
#define SPAWN_GAME__HPP__

#include <thread>
#include "../domain/game.hpp"

class SpawnGame: public Game
{
public:
    static Game::Movable make(
        Score      &     _win_score,
        Board::Movable & _board,
        Player     &     _player,
        Observer    &    _observer);

    virtual ~SpawnGame();

private:
    explicit SpawnGame(
        Score      &     _win_score,
        Board::Movable & _board,
        Player     &     _player,
        Observer    &    _observer);

    std::thread m_thread;
};

#endif
