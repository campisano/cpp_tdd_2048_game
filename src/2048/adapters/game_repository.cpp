#include "game_repository.hpp"

void GameRepository::saveCurrent(Game::Movable & _game)
{
    m_game = std::move(_game);
}

Game & GameRepository::getCurrent()
{
    return * m_game;
}
