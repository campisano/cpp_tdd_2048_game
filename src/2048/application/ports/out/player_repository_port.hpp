#ifndef PLAYER_REPOSITORY_PORT__HPP__
#define PLAYER_REPOSITORY_PORT__HPP__

#include "../../human_player.hpp"

class PlayerRepositoryPort
{
public:
    virtual ~PlayerRepositoryPort() = default;

    virtual void          saveCurrent(HumanPlayer::Movable & _player) = 0;
    virtual HumanPlayer & getCurrent() = 0;
};

#endif
