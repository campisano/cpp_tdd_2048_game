#ifndef GAME_REPOSITORY_PORT__HPP__
#define GAME_REPOSITORY_PORT__HPP__

#include "../../../domain/game.hpp"

class GameRepositoryPort
{
public:
    virtual ~GameRepositoryPort() = default;

    virtual void   saveCurrent(Game::Movable & _game) = 0;
    virtual Game & getCurrent() = 0;
};

#endif
