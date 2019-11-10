#include "number.hpp"

#include <stdexcept>

namespace
{
bool isPowerOfTwo(uint32_t _num)
{
    return (_num > 0) && ((_num & (_num - 1)) == 0);
}
}

Number::Number(uint32_t _value, const Position & _position)
    : m_position(_position)
{
    if(_value < 2)
    {
        throw std::runtime_error("value cannot be less than 2");
    }

    if(! isPowerOfTwo(_value))
    {
        throw std::runtime_error("value must be power of 2");
    }

    m_value = _value;
}

Number::~Number()
{
}

uint32_t Number::value()
{
    return m_value;
}

const Position & Number::position()
{
    return m_position;
}
