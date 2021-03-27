#include "move_usecase.hpp"

#include <stdexcept>
#include "../../domain/direction.hpp"

namespace
{
Direction convert(MoveUsecase::Direction & _direction);
}

MoveUsecase::Movable MoveUsecase::make(PlayerRepositoryPort & _player_repo)
{
    return Movable(new MoveUsecase(_player_repo));
}

MoveUsecase::MoveUsecase(PlayerRepositoryPort & _player_repo)
    : m_player_repo(_player_repo)
{
}

MoveUsecase::~MoveUsecase()
{
}

void MoveUsecase::execute(Direction & _direction)
{
    auto direction = convert(_direction);
    auto & player = m_player_repo.getCurrent();
    player.setNextMove(direction);
}

namespace
{
Direction convert(MoveUsecase::Direction & _direction)
{
    switch(_direction)
    {
    case MoveUsecase::Direction::left:
        return Direction::left;
    case MoveUsecase::Direction::right:
        return Direction::right;
    case MoveUsecase::Direction::up:
        return Direction::up;
    case MoveUsecase::Direction::down:
        return Direction::down;
    default:
        throw std::runtime_error("unknown direction");
    }
}
}
