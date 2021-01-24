#ifndef BOARD__HPP__
#define BOARD__HPP__

#include <cstdint>
#include <memory>
#include <vector>
#include "../../common/move_only.hpp"
#include "direction.hpp"
#include "number.hpp"
#include "position.hpp"

class Board : MoveOnly
{
public:
    using Row     = std::vector<Number::Value>;
    using Array   = std::vector<Row>;
    using Size    = int32_t;
    using Movable = std::unique_ptr<Board>;

    static Movable make(Size _rows, Size _cols);

    virtual ~Board();

protected:
    explicit Board(Size _rows, Size _cols);

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
    virtual Position & at(Size _row, Size _col);

private:
    bool slideLeft();
    bool slideRight();
    bool slideUp();
    bool slideDown();
    void clearMergeState();

    const Size  m_rows;
    const Size  m_cols;
    Position ** m_positions;
};

#endif
