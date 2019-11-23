#ifndef BOARD__HPP__
#define BOARD__HPP__

#include <cstdint>
#include "position.hpp"

class Board
{
public:
    explicit Board();
    Board(const Board &) = delete;
    Board(Board &&) = default;
    virtual ~Board();

    Board & operator=(const Board &) = delete;
    Board & operator=(Board &&) = default;

public:
    std::size_t size() const;
    Position & at(uint8_t _row, uint8_t _col);
    void slideLeft();

private:
    static const uint8_t EDGE_SIZE = 4;
    Position m_positions[EDGE_SIZE][EDGE_SIZE];
};

#endif
