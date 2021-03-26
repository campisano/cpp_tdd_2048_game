#ifndef START_GAME_USECASE__HPP__
#define START_GAME_USECASE__HPP__

#include <memory>
#include "../game_repository.hpp"
#include "../ports/start_game_usecase_port.hpp"
#include "../../domain/observer.hpp"
#include "../../domain/player.hpp"
#include "../../../common/move_only.hpp"

class StartGameUsecase : public StartGameUsecasePort, MoveOnly
{
public:
    using Movable = std::unique_ptr<StartGameUsecase>;

    static Movable make(GameRepository & _grp, Player & _ply, Observer & _obs);

    virtual ~StartGameUsecase();

    void execute(int _score, int _rows, int _cols);

private:
    explicit StartGameUsecase(
        GameRepository & _grp, Player & _ply, Observer & _obs);

    GameRepository & m_grp;
    Player     &     m_ply;
    Observer    &    m_obs;
};

#endif
