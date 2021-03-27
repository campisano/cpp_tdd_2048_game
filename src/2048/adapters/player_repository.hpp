#ifndef PLAYER_REPOSITORY__HPP__
#define PLAYER_REPOSITORY__HPP__

#include "../../common/move_only.hpp"
#include "../application/ports/out/player_repository_port.hpp"
#include "../application/human_player.hpp"

class PlayerRepository : public PlayerRepositoryPort, MoveOnly
{
public:
    void          saveCurrent(HumanPlayer::Movable & _player);
    HumanPlayer & getCurrent();

private:
    HumanPlayer::Movable m_player;
};

#endif
