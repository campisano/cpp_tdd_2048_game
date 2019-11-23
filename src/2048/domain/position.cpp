#include "position.hpp"

#include <stdexcept>

Position::Position() : m_left(NULL), m_right(NULL), m_up(NULL), m_down(NULL)
{
}

Position::~Position()
{
}

bool Position::hasNumber() const
{
    if(m_number)
    {
        return true;
    }

    return false;
}

const Number::Movable & Position::number() const
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

void Position::left(Position & _left)
{
    m_left = & _left;
}

bool Position::hasRight() const
{
    return m_right != NULL;
}

Position & Position::right() const
{
    if(! hasRight())
    {
        throw std::runtime_error("there is no right position");
    }

    return * m_right;
}

void Position::right(Position & _right)
{
    m_right = & _right;
}

bool Position::hasUp() const
{
    return m_up != NULL;
}

Position & Position::up() const
{
    if(! hasUp())
    {
        throw std::runtime_error("there is no up position");
    }

    return * m_up;
}

void Position::up(Position & _up)
{
    m_up = & _up;
}

bool Position::hasDown() const
{
    return m_down != NULL;
}

Position & Position::down() const
{
    if(! hasDown())
    {
        throw std::runtime_error("there is no down position");
    }

    return * m_down;
}

void Position::down(Position & _down)
{
    m_down = & _down;
}

void Position::slideLeft()
{
    auto left = & this->left();

    while(left->hasLeft() && (! left->left().hasNumber()))
    {
        left = & left->left();
    }

    left->place(m_number);
}
