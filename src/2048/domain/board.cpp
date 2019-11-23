#include "board.hpp"

#include <stdexcept>

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

Position & Board::at(uint8_t _row, uint8_t _col)
{
    if(_row >= EDGE_SIZE || _col >= EDGE_SIZE)
    {
        throw std::runtime_error("out of board boundaries");
    }

    return m_positions[_row][_col];
}

void Board::slideLeft()
{
    for(auto row = 0; row < EDGE_SIZE; ++row)
    {
        for(auto col = 1; col < EDGE_SIZE; ++col)
        {
            if(m_positions[row][col].hasNumber())
            {
                slideLeftFrom(m_positions[row][col]);
            }
        }
    }
}

void Board::slideLeftFrom(Position & _position)
{
    auto left = & _position.left();

    while(left->hasLeft() && (! left->left().hasNumber()))
    {
        left = & left->left();
    }

    _position.transferTo(*left);
}
