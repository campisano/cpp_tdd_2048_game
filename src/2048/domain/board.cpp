#include "board.hpp"
#include <stdexcept>

namespace
{
inline bool hasSpaceInDirection(
    Position & _position, bool (Position::*_has_direction)() const)
{
    return (_position.*_has_direction)();
}

inline Position & positionAtDirection(
    Position & _position, Position & (Position::*_direction)() const)
{
    return (_position.*_direction)();
}

void slideFrom(
    Position & _position,
    bool (Position::*_has_direction)() const,
    Position & (Position::*_direction)() const
)
{
    auto dest = & _position;

    while(hasSpaceInDirection(* dest, _has_direction) && (
                !positionAtDirection(* dest, _direction).hasNumber() ||
                positionAtDirection(* dest, _direction).number()->canMerge(
                    * _position.number())
            ))
    {
        dest = & (dest->*_direction)();
    }

    if(dest != & _position)
    {
        _position.transferTo(* dest);
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
