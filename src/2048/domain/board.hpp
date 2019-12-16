#ifndef BOARD__HPP__
#define BOARD__HPP__

#include <cstdint>
#include "position.hpp"

class Board
{
public:
    using Size = uint16_t;

public:
    explicit Board();
    Board(const Board &) = delete;
    Board(Board &&) = default;
    virtual ~Board();

    Board & operator=(const Board &) = delete;
    Board & operator=(Board &&) = default;

public:
    void slideLeft();
    void slideRight();
    void slideUp();
    void slideDown();
    void placeRandomNumber();

protected:
    virtual Size size() const;
    virtual Position & at(Size _row, Size _column);
    virtual Size count() const;

private:
    static const Size EDGE_SIZE = 4;
    Position m_positions[EDGE_SIZE][EDGE_SIZE];
};

#endif
