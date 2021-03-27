#include "number.hpp"

#include <stdexcept>

namespace
{
bool isPowerOfTwo(Number::Value _number);
}

Number::Number(Value _value) : m_value(_value), m_merged(false)
{
    if(m_value < 2)
    {
        throw std::runtime_error("value cannot be less than 2");
    }

    if(! isPowerOfTwo(m_value))
    {
        throw std::runtime_error("value must be power of 2");
    }
}

Number::~Number()
{
}

Number::Movable Number::make(Value _value)
{
    return Movable(new Number(_value));
}

Number::Value Number::value() const
{
    return m_value;
}

bool Number::canMerge(const Number & _number) const
{
    return !m_merged && !_number.m_merged && _number.value() == m_value;
}

void Number::merge(Movable & _number)
{
    if(! canMerge(* _number))
    {
        throw std::runtime_error(
            "merging numbers must have the same value"
            " and must have not been merged");
    }

    m_value += _number->value();
    _number.reset();
    m_merged = true;
}

void Number::clearMergeState()
{
    m_merged = false;
}

namespace
{
bool isPowerOfTwo(Number::Value _number)
{
    return (_number > 0) && ((_number & (_number - 1)) == 0);
}
}
