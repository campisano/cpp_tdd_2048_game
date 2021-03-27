#include "spawn_game.hpp"

SpawnGame::Movable SpawnGame::make(
    Score      &     _win_score,
    Board::Movable & _board,
    Player     &     _player,
    Observer    &    _observer)
{
    return Movable(
               new SpawnGame(_win_score,
                             _board,
                             _player,
                             _observer));
}

SpawnGame::SpawnGame(
    Score      &     _win_score,
    Board::Movable & _board,
    Player     &     _player,
    Observer    &    _observer)
    : Game(_win_score, _board, _player, _observer)
{
}

SpawnGame::~SpawnGame()
{
}

void SpawnGame::spawn()
{
    m_thread = std::thread(&Game::start, this);
}

void SpawnGame::join()
{
    m_thread.join();
}
