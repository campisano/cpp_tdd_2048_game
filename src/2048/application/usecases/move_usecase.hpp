#ifndef MOVE_USECASE__HPP__
#define MOVE_USECASE__HPP__

#include <memory>
#include "../../../common/move_only.hpp"
#include "../ports/in/move_usecase_port.hpp"
#include "../ports/out/player_repository_port.hpp"

class MoveUsecase : public MoveUsecasePort, MoveOnly
{
public:
    using Movable = std::unique_ptr<MoveUsecase>;

    static Movable make(PlayerRepositoryPort & _player_repo);

    virtual ~MoveUsecase();

    void execute(Direction & _direction);

private:
    explicit MoveUsecase(PlayerRepositoryPort & _player_repo);

    PlayerRepositoryPort & m_player_repo;
};

#endif
