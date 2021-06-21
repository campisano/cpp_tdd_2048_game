#ifndef GAME_REPOSITORY__HPP__
#define GAME_REPOSITORY__HPP__

#include "../../common/move_only.hpp"
#include "../application/ports/out/game_repository_port.hpp"
#include "../domain/game.hpp"

class GameRepository : public GameRepositoryPort, MoveOnly
{
public:
    void saveCurrent(Game::Movable & _game);
    Game & getCurrent();

private:
    Game::Movable m_game;
};

#endif
