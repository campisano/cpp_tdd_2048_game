#ifndef START_GAME_USECASE__HPP__
#define START_GAME_USECASE__HPP__

#include <memory>
#include "../../../common/move_only.hpp"
#include "../../domain/observer.hpp"
#include "../ports/in/start_game_usecase_port.hpp"
#include "../ports/out/game_repository_port.hpp"
#include "../ports/out/player_repository_port.hpp"

class StartGameUsecase : public StartGameUsecasePort, MoveOnly
{
public:
    using Movable = std::unique_ptr<StartGameUsecase>;

    static Movable make(GameRepositoryPort & _game_repo,
                        PlayerRepositoryPort & _player_repo,
                        Observer & _observer);

    virtual ~StartGameUsecase();

    void execute(int _score, int _rows, int _cols);

private:
    explicit StartGameUsecase(GameRepositoryPort & _game_repo,
                              PlayerRepositoryPort & _player_repo,
                              Observer & _observer);

    GameRepositoryPort  &  m_game_repo;
    PlayerRepositoryPort & m_player_repo;
    Observer       &       m_observer;
};

#endif
