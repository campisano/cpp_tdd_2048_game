#include "direction.hpp"

std::ostream & operator<<(std::ostream & _out, const Direction _direction)
{
    switch(_direction)
    {
    case Direction::left:
        return _out << "left";
    case Direction::right:
        return _out << "right";
    case Direction::up:
        return _out << "up";
    case Direction::down:
        return _out << "down";
    }
}
