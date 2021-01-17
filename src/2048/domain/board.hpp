#ifndef BOARD__HPP__
#define BOARD__HPP__

#include <cstdint>
#include <memory>
#include "position.hpp"

class Board
{
public:
    using Movable = std::unique_ptr<Board>;
    using Size = uint16_t; //TODO use of unsigned values can mask logic errors

public:
    explicit Board();
    Board(const Board &) = delete;
    Board(Board &&)      = default;
    virtual ~Board();

    Board & operator=(const Board &) = delete;
    Board & operator=(Board &&)      = default;

public:
    void slideLeft();
    void slideRight();
    void slideUp();
    void slideDown();
    void placeNumberRandomly(Number::Movable & _number);

    Size size()  const;
    Size count() const;

protected:
    virtual Position & at(Size _row, Size _column);

private:
    static const Size EDGE_SIZE = 4;
    Position m_positions[EDGE_SIZE][EDGE_SIZE];
};

#endif
