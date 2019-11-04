#include "number.hpp"

#include <stdexcept>

Number::Number(uint32_t _value)
{
    if(_value < 2)
    {
        throw std::runtime_error("value cannot be less than 2");
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
