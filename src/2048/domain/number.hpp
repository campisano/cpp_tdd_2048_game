#ifndef NUMBER__HPP__
#define NUMBER__HPP__

#include <cstdint>

class Number
{
public:
    explicit Number(uint32_t _value);
    Number(const Number &) = delete;
    Number(Number &&) = default;
    virtual ~Number();

    Number & operator=(const Number &) = delete;
    Number & operator=(Number &&) = default;

public:
    uint32_t value();

private:
    uint32_t m_value;
};

#endif
