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
    bool hasNumber() const;
    const Number::Movable & number() const;
    void place(Number::Movable & _number);

    bool hasLeft() const;
    Position & left() const;
    void left(Position & _position);
    bool hasRight() const;
    Position & right() const;
    void right(Position & _position);
    bool hasUp() const;
    Position & up() const;
    void up(Position & _position);
    bool hasDown() const;
    Position & down() const;
    void down(Position & _position);

    void transferTo(Position & _position);

private:
    Number::Movable m_number;
    Position * m_left;
    Position * m_right;
    Position * m_up;
    Position * m_down;
};

#endif
