#include "position.hpp"

#include <stdexcept>

Position::Position()
{
}

Position::~Position()
{
}

const MovableNum & Position::number()
{
    return m_number;
}

void Position::place(MovableNum & _number)
{
    if(m_number)
    {
        throw std::runtime_error("position already contain a number");
    }

    m_number = std::move(_number);
}
