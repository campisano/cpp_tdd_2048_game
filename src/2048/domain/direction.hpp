#ifndef DIRECTION__HPP__
#define DIRECTION__HPP__

#include <ostream>

enum class Direction
{
    left,
    right,
    up,
    down
};

std::ostream & operator<<(std::ostream & _out, const Direction _direction);

#endif
