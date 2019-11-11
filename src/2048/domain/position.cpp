#include "position.hpp"

#include <stdexcept>

Position::Position()
{
    m_left = NULL;
}

Position::~Position()
{
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
    return m_left != NULL;
}

Position & Position::left() const
{
    if(! hasLeft())
    {
        throw std::runtime_error("there is no left position");
    }

    return * m_left;
}

void Position::left(Position & _position)
{
    m_left = & _position;
}
