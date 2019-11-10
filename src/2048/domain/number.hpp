#ifndef NUMBER__HPP__
#define NUMBER__HPP__

#include <cstdint>
#include "position.hpp"

class Number
{
public:
    explicit Number(uint32_t _value, const Position & _position);
    Number(const Number &) = delete;
    Number(Number &&) = default;
    virtual ~Number();

    Number & operator=(const Number &) = delete;
    Number & operator=(Number &&) = default;

public:
    uint32_t value();
    const Position & position();

private:
    uint32_t m_value;
    const Position & m_position;
};

#endif
