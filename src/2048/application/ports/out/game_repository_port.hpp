#ifndef GAME_REPOSITORY_PORT__HPP__
#define GAME_REPOSITORY_PORT__HPP__

#include "../../spawn_game.hpp"

class GameRepositoryPort
{
public:
    virtual ~GameRepositoryPort() = default;

    virtual void        saveCurrent(SpawnGame::Movable & _game) = 0;
    virtual SpawnGame & getCurrent() = 0;
};

#endif
