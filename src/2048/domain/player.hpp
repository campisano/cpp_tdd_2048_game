#ifndef PLAYER__HPP__
#define PLAYER__HPP__

#include "direction.hpp"

class Player
{
public:
    virtual ~Player() = default;

    virtual Direction chooseDirection() = 0;
};

#endif
