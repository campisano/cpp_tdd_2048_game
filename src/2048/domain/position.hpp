#ifndef POSITION__HPP__
#define POSITION__HPP__

#include <array>
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

    void adjacents(
        Position * _left, Position * _right,
        Position * _up, Position * _down);

    bool hasLeft() const;
    Position & left() const;
    bool hasRight() const;
    Position & right() const;
    bool hasUp() const;
    Position & up() const;
    bool hasDown() const;
    Position & down() const;

private:
    Number::Movable m_number;
    std::array<Position *, 4> m_adjacents;
};

#endif
