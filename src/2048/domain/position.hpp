#ifndef POSITION__HPP__
#define POSITION__HPP__

#include <memory>
#include "number.hpp"

class Position
{
public:
    explicit Position();
    Position(const Position &) = delete;
    Position(Position &&) = default;
    virtual ~Position();

    Position & operator=(const Position &) = delete;
    Position & operator=(Position &&) = default;

public:
    const Number::Movable & number();
    void place(Number::Movable & _number);

private:
    Number::Movable m_number;
};

#endif
