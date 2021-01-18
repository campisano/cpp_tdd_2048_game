#include "board.hpp"
#include <random>
#include <stdexcept>

namespace
{
void slideFrom(
    Position & _position,
    bool (Position::*_has_direction)() const,
    Position & (Position::*_next_direction)() const
)
{
    Position * dest = & _position;
    Position * next;

    while((dest->*_has_direction)())
    {
        next = & (dest->*_next_direction)();

        if(next->hasNumber())
        {
            if(next->number()->canMerge(* _position.number()))
            {
                dest = next;
            }

            break;
        }

        dest = next;
    }

    if(dest != & _position)
    {
        _position.transferTo(* dest);
    }
}

inline Board::Size generateRandomPlace(Board::Size _limit)
{
    std::random_device                 r;
    std::default_random_engine         e(r());
    std::uniform_int_distribution<int> dist(0, _limit);
    return dist(e);
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

void Board::slide(Direction _direction)
{
    if(_direction == Direction::left)
    {
        slideLeft();
    }
    else if(_direction == Direction::right)
    {
        slideRight();
    }
    else if(_direction == Direction::up)
    {
        slideUp();
    }
    else if(_direction == Direction::down)
    {
        slideDown();
    }
    else
    {
        throw std::runtime_error("algorithm fault");
    }

    clearMergeState();
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

void Board::placeNumberRandomly(Number::Movable & _number)
{
    Size free_pos = size() - count();

    if(free_pos == 0)
    {
        throw std::runtime_error("no space left on board");
    }

    Size rand_pos = generateRandomPlace(free_pos - 1);

    for(auto row = 0; row < EDGE_SIZE; ++row)
    {
        for(auto col = 0; col < EDGE_SIZE; ++col)
        {
            if(! m_positions[row][col].hasNumber())
            {
                if(rand_pos == 0)
                {
                    m_positions[row][col].place(_number);
                    return;
                }
                else
                {
                    --rand_pos;
                }
            }
        }
    }

    throw std::runtime_error("algorithm fault");
}

Board::Size Board::size() const
{
    return EDGE_SIZE * EDGE_SIZE;
}

Position & Board::at(Size _row, Size _column)
{
    if(_row >= EDGE_SIZE || _column >= EDGE_SIZE)
    {
        throw std::runtime_error("out of board boundaries");
    }

    return m_positions[_row][_column];
}

const Position & Board::at(Size _row, Size _column) const
{
    if(_row >= EDGE_SIZE || _column >= EDGE_SIZE)
    {
        throw std::runtime_error("out of board boundaries");
    }

    return m_positions[_row][_column];
}

Board::Size Board::count() const
{
    Size count = 0;
    for(auto row = 0; row < EDGE_SIZE; ++row)
    {
        for(auto col = 0; col < EDGE_SIZE; ++col)
        {
            if(m_positions[row][col].hasNumber())
            {
                ++count;
            }
        }
    }

    return count;
}

Board::Size Board::getMaxNumber() const
{
    Size max = 0;
    Size num;
    for(auto row = 0; row < EDGE_SIZE; ++row)
    {
        for(auto col = 0; col < EDGE_SIZE; ++col)
        {
            if(m_positions[row][col].hasNumber())
            {
                num = m_positions[row][col].number()->value();
                if(num > max)
                {
                    max = num;
                }
            }
        }
    }

    return max;
}

bool Board::hasFreeSpaces() const
{
    return (size() - count()) > 0;
}

bool Board::canSlide() const
{
    if(hasFreeSpaces())
    {
        return true;
    }

    const Position * pos;

    for(auto row = 0; row < EDGE_SIZE; ++row)
    {
        for(auto col = 0; col < EDGE_SIZE; ++col)
        {
            pos = & m_positions[row][col];
            if(
                pos->hasNumber()
                && (
                    (pos->hasLeft()
                     && pos->number()->canMerge(* pos->left().number()))
                    ||
                    (pos->hasRight()
                     && pos->number()->canMerge(* pos->right().number()))
                    ||
                    (pos->hasUp()
                     && pos->number()->canMerge(* pos->up().number()))
                    ||
                    (pos->hasDown()
                     && pos->number()->canMerge(* pos->down().number()))
                )
            )
            {
                return true;
            }
        }
    }

    return false;
}

void Board::clearMergeState()
{
    for(auto col = 0; col < EDGE_SIZE; ++col)
    {
        for(auto row = 1; row < EDGE_SIZE; ++row)
        {
            if(m_positions[row][col].hasNumber())
            {
                m_positions[row][col].number()->clearMergeState();
            }
        }
    }
}
