#ifndef GAME_REPOSITORY__HPP__
#define GAME_REPOSITORY__HPP__

#include "../../common/move_only.hpp"
#include "../application/ports/out/game_repository_port.hpp"
#include "../application/spawn_game.hpp"

class GameRepository : public GameRepositoryPort, MoveOnly
{
public:
    void        saveCurrent(SpawnGame::Movable & _game);
    SpawnGame & getCurrent();

private:
    SpawnGame::Movable m_game;
};

#endif
