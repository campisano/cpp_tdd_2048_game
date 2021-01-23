#ifndef BOARD__HPP__
#define BOARD__HPP__

#include <cstdint>
#include <memory>
#include <vector>
#include "direction.hpp"
#include "number.hpp"
#include "position.hpp"

class Board
{
public:
    using Row   = std::vector<Number::Value>;
    using Array = std::vector<Row>;
    using Size  = int16_t;

    using Movable = std::unique_ptr<Board>;
    static Movable make();

protected:
    explicit Board();

public:
    Board(const Board &) = delete;
    Board(Board &&)      = default;
    virtual ~Board();

    Board & operator=(const Board &) = delete;
    Board & operator=(Board &&)      = default;

public:
    bool slide(Direction _direction);
    void placeNumberRandomly(Number::Movable & _number);

    Size size()  const;
    Size count() const;

    Size getMaxNumber()  const;
    bool hasFreeSpaces() const;
    bool canSlide()      const;

    Array status() const;

protected:
    virtual Position & at(Size _row, Size _column);

private:
    bool slideLeft();
    bool slideRight();
    bool slideUp();
    bool slideDown();
    void clearMergeState();

    static const Size EDGE_SIZE = 4;
    Position m_positions[EDGE_SIZE][EDGE_SIZE];
};

#endif
