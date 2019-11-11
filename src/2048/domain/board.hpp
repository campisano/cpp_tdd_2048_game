#ifndef BOARD__HPP__
#define BOARD__HPP__

#include <array>
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
    uint32_t size();

private:
    static const uint8_t BOARD_SIZE = 16;
    std::array<Position, BOARD_SIZE> m_array;
};

#endif
