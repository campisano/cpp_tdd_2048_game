#include "number.hpp"

Number::Number(uint32_t _value) : m_value(_value)
{
}

Number::~Number()
{
}

uint32_t Number::value()
{
    return m_value;
}
