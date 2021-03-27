#ifndef SPAWN_GAME__HPP__
#define SPAWN_GAME__HPP__

#include <memory>
#include <thread>
#include "../domain/game.hpp"

class SpawnGame: public Game
{
public:
    using Movable = std::unique_ptr<SpawnGame>;

    static Movable make(
        Score      &     _win_score,
        Board::Movable & _board,
        Player     &     _player,
        Observer    &    _observer);

    virtual ~SpawnGame();

    void spawn();
    void join();

private:
    explicit SpawnGame(
        Score      &     _win_score,
        Board::Movable & _board,
        Player     &     _player,
        Observer    &    _observer);

    std::thread m_thread;
};

#endif
