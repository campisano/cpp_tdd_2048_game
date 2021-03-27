#include "game_repository.hpp"

void GameRepository::saveCurrent(SpawnGame::Movable & _game)
{
    m_game = std::move(_game);
}

SpawnGame & GameRepository::getCurrent()
{
    return * m_game;
}
