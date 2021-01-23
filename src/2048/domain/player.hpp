#ifndef PLAYER__HPP__
#define PLAYER__HPP__

#include <memory>
#include "../../common/move_only.hpp"
#include "direction.hpp"

class Player : MoveOnly
{
public:
    using Movable = std::unique_ptr<Player>;

    virtual ~Player() = default;

    virtual Direction chooseDirection() = 0;
};

#endif
