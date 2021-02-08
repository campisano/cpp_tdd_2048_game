#include "game_repository.hpp"

Game::Movable GameRepository::create(
    Score      &     _win_score,
    Board::Movable & _board,
    Player     &     _player,
    Observer    &    _observer)
{
    return Game::make(_win_score, _board, _player, _observer);
}
