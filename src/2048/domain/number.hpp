#ifndef NUMBER__HPP__
#define NUMBER__HPP__

#include <cstdint>

using Position = void*;

class Number
{
public:
    explicit Number(uint32_t _value, Position _position);
    Number(const Number &) = delete;
    Number(Number &&) = default;
    virtual ~Number();

    Number & operator=(const Number &) = delete;
    Number & operator=(Number &&) = default;

public:
    uint32_t value();
    Position position();

private:
    uint32_t m_value;
    Position m_position;
};

#endif
