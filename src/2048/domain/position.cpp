#include "position.hpp"

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
