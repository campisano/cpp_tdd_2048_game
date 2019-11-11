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
    const std::unique_ptr<Number> & number();
    void place(std::unique_ptr<Number> & _number);

private:
    std::unique_ptr<Number> m_number;
};

#endif
