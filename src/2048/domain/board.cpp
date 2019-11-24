#include "board.hpp"

#include <stdexcept>

namespace
{
void slideFrom(
    Position & _position,
    bool (Position::*_has_direction)() const,
    Position & (Position::*_direction)() const
)
{
    auto slide_destination = & _position;

    while(
        ((slide_destination->*_has_direction)()) &&
        (!(slide_destination->*_direction)().hasNumber()))
    {
        slide_destination = & (slide_destination->*_direction)();
    }

    if(slide_destination != & _position)
    {
        _position.transferTo(* slide_destination);
    }
}
}

Board::Board()
{
    for(auto row = 0; row < EDGE_SIZE; ++row)
    {
        for(auto col = 0; col < EDGE_SIZE; ++col)
        {
            if(row > 0)
            {
                m_positions[row][col].up(m_positions[row - 1][col]);
            }
            if(row < (EDGE_SIZE - 1))
            {
                m_positions[row][col].down(m_positions[row + 1][col]);
            }
            if(col > 0)
            {
                m_positions[row][col].left(m_positions[row][col - 1]);
            }
            if(col < (EDGE_SIZE - 1))
            {
                m_positions[row][col].right(m_positions[row][col + 1]);
            }
        }
    }
}

Board::~Board()
{
}

std::size_t Board::size() const
{
    return EDGE_SIZE * EDGE_SIZE;
}

Position & Board::at(uint8_t _row, uint8_t _column)
{
    if(_row >= EDGE_SIZE || _column >= EDGE_SIZE)
    {
        throw std::runtime_error("out of board boundaries");
    }

    return m_positions[_row][_column];
}

void Board::slideLeft()
{
    for(auto row = 0; row < EDGE_SIZE; ++row)
    {
        for(auto col = 1; col < EDGE_SIZE; ++col)
        {
            if(m_positions[row][col].hasNumber())
            {
                slideFrom(
                    m_positions[row][col],
                    &Position::hasLeft,
                    &Position::left);
            }
        }
    }
}

void Board::slideRight()
{
    for(auto row = 0; row < EDGE_SIZE; ++row)
    {
        for(auto col = EDGE_SIZE - 2; col >= 0; --col)
        {
            if(m_positions[row][col].hasNumber())
            {
                slideFrom(
                    m_positions[row][col],
                    &Position::hasRight,
                    &Position::right);
            }
        }
    }
}

void Board::slideUp()
{
    for(auto col = 0; col < EDGE_SIZE; ++col)
    {
        for(auto row = 1; row < EDGE_SIZE; ++row)
        {
            if(m_positions[row][col].hasNumber())
            {
                slideFrom(
                    m_positions[row][col],
                    &Position::hasUp,
                    &Position::up);
            }
        }
    }
}

void Board::slideDown()
{
    for(auto col = 0; col < EDGE_SIZE; ++col)
    {
        for(auto row = EDGE_SIZE - 2; row >= 0; --row)
        {
            if(m_positions[row][col].hasNumber())
            {
                slideFrom(
                    m_positions[row][col],
                    &Position::hasDown,
                    &Position::down);
            }
        }
    }
}
