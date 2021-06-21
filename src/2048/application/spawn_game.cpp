#include "spawn_game.hpp"

Game::Movable SpawnGame::make(
    Score      &     _win_score,
    Board::Movable & _board,
    Player     &     _player,
    Observer    &    _observer)
{
    return Game::Movable(
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
    m_thread = std::thread(&Game::start, this);
}

SpawnGame::~SpawnGame()
{
    m_thread.join();
}
