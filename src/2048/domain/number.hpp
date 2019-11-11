#ifndef NUMBER__HPP__
#define NUMBER__HPP__

#include <cstdint>
#include <memory>

class Number;
using MovableNum = std::unique_ptr<Number>;
using Value = uint32_t;

class Number
{
public:
    explicit Number(Value _value);
    Number(const Number &) = delete;
    Number(Number &&) = default;
    virtual ~Number();

    Number & operator=(const Number &) = delete;
    Number & operator=(Number &&) = default;

    static MovableNum make(Value _value);

public:
    Value value();

private:
    Value m_value;
};

#endif
