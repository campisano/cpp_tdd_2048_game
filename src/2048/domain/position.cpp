#include "position.hpp"

#include <stdexcept>

Position::Position()
{
}

Position::~Position()
{
}

const std::unique_ptr<Number> & Position::number()
{
    return m_number;
}

void Position::place(std::unique_ptr<Number> & _number)
{
    if(m_number)
    {
        throw std::runtime_error("position already contain a number");
    }

    m_number = std::move(_number);
}
