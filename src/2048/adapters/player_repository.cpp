#include "player_repository.hpp"

void PlayerRepository::saveCurrent(HumanPlayer::Movable & _player)
{
    m_player = std::move(_player);
}

HumanPlayer & PlayerRepository::getCurrent()
{
    return * m_player;
}
