#include "position.hpp"

#include <stdexcept>

namespace
{
const unsigned int LEFT  = 0;
const unsigned int RIGHT = 1;
const unsigned int UP    = 2;
const unsigned int DOWN  = 3;
}

Position::Position()
{
    adjacents(NULL, NULL, NULL, NULL);
}

Position::~Position()
{
}

void Position::adjacents(
    Position * _left, Position * _right,
    Position * _up, Position * _down)
{
    m_adjacents[LEFT]  = _left;
    m_adjacents[RIGHT] = _right;
    m_adjacents[UP]    = _up;
    m_adjacents[DOWN]  = _down;
}

const Number::Movable & Position::number()
{
    return m_number;
}

void Position::place(Number::Movable & _number)
{
    if(m_number)
    {
        throw std::runtime_error("position already contain a number");
    }

    m_number = std::move(_number);
}

bool Position::hasLeft() const
{
    return m_adjacents[LEFT] != NULL;
}

Position & Position::left() const
{
    if(! hasLeft())
    {
        throw std::runtime_error("there is no left position");
    }

    return * m_adjacents[LEFT];
}

bool Position::hasRight() const
{
    return m_adjacents[RIGHT] != NULL;
}

Position & Position::right() const
{
    if(! hasRight())
    {
        throw std::runtime_error("there is no right position");
    }

    return * m_adjacents[RIGHT];
}

bool Position::hasUp() const
{
    return m_adjacents[UP] != NULL;
}

Position & Position::up() const
{
    if(! hasUp())
    {
        throw std::runtime_error("there is no up position");
    }

    return * m_adjacents[UP];
}

bool Position::hasDown() const
{
    return m_adjacents[DOWN] != NULL;
}

Position & Position::down() const
{
    if(! hasDown())
    {
        throw std::runtime_error("there is no down position");
    }

    return * m_adjacents[DOWN];
}
