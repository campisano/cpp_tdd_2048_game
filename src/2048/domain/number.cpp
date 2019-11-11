#include "number.hpp"

#include <stdexcept>

namespace
{
bool isPowerOfTwo(Number::Value _num)
{
    return (_num > 0) && ((_num & (_num - 1)) == 0);
}
}

Number::Number(Value _value)
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

Number::Movable Number::make(Value _value)
{
    return Movable(new Number(_value));
}

Number::Value Number::value()
{
    return m_value;
}
