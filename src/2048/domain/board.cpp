#include "board.hpp"
#include <random>
#include <stdexcept>

namespace
{
bool slideFromPositionToDirection(
    Position & _position,
    bool (Position::*_has_direction)() const,
    Position & (Position::*_next_direction)() const);

Board::Size generateRandomPlace(Board::Size _limit);
}

Board::Board()
{
    for(Size row = 0; row < EDGE_SIZE; ++row)
    {
        for(Size col = 0; col < EDGE_SIZE; ++col)
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

Board::Movable Board::make()
{
    return Movable(new Board());
}

bool Board::slide(Direction _direction)
{
    bool valid_move;

    if(_direction == Direction::left)
    {
        valid_move = slideLeft();
    }
    else if(_direction == Direction::right)
    {
        valid_move = slideRight();
    }
    else if(_direction == Direction::up)
    {
        valid_move = slideUp();
    }
    else if(_direction == Direction::down)
    {
        valid_move = slideDown();
    }
    else
    {
        throw std::runtime_error("algorithm fault");
    }

    clearMergeState();

    return valid_move;
}

bool Board::slideLeft()
{
    bool any_valid_slide = false;
    bool valid_slide;

    for(Size row = 0; row < EDGE_SIZE; ++row)
    {
        for(Size col = 1; col < EDGE_SIZE; ++col)
        {
            if(m_positions[row][col].hasNumber())
            {
                valid_slide = slideFromPositionToDirection(
                                  m_positions[row][col],
                                  &Position::hasLeft,
                                  &Position::left);

                if(valid_slide && ! any_valid_slide)
                {
                    any_valid_slide = valid_slide;
                }
            }
        }
    }

    return any_valid_slide;
}

bool Board::slideRight()
{
    bool any_valid_slide = false;
    bool valid_slide;

    for(Size row = 0; row < EDGE_SIZE; ++row)
    {
        for(Size col = EDGE_SIZE - 2; col >= 0; --col)
        {
            if(m_positions[row][col].hasNumber())
            {
                valid_slide = slideFromPositionToDirection(
                                  m_positions[row][col],
                                  &Position::hasRight,
                                  &Position::right);

                if(valid_slide && ! any_valid_slide)
                {
                    any_valid_slide = valid_slide;
                }
            }
        }
    }

    return any_valid_slide;
}

bool Board::slideUp()
{
    bool any_valid_slide = false;
    bool valid_slide;

    for(Size col = 0; col < EDGE_SIZE; ++col)
    {
        for(Size row = 1; row < EDGE_SIZE; ++row)
        {
            if(m_positions[row][col].hasNumber())
            {
                valid_slide = slideFromPositionToDirection(
                                  m_positions[row][col],
                                  &Position::hasUp,
                                  &Position::up);

                if(valid_slide && ! any_valid_slide)
                {
                    any_valid_slide = valid_slide;
                }
            }
        }
    }

    return any_valid_slide;
}

bool Board::slideDown()
{
    bool any_valid_slide = false;
    bool valid_slide;

    for(Size col = 0; col < EDGE_SIZE; ++col)
    {
        for(Size row = EDGE_SIZE - 2; row >= 0; --row)
        {
            if(m_positions[row][col].hasNumber())
            {
                valid_slide = slideFromPositionToDirection(
                                  m_positions[row][col],
                                  &Position::hasDown,
                                  &Position::down);

                if(valid_slide && ! any_valid_slide)
                {
                    any_valid_slide = valid_slide;
                }
            }
        }
    }

    return any_valid_slide;
}

void Board::placeNumberRandomly(Number::Movable & _number)
{
    Size free_pos = size() - count();

    if(free_pos == 0)
    {
        throw std::runtime_error("no space left on board");
    }

    Size rand_pos = generateRandomPlace(free_pos - 1);

    for(Size row = 0; row < EDGE_SIZE; ++row)
    {
        for(Size col = 0; col < EDGE_SIZE; ++col)
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
    if(
        _row < 0 || _column < 0 ||
        _row >= EDGE_SIZE || _column >= EDGE_SIZE)
    {
        throw std::runtime_error("out of board boundaries");
    }

    return m_positions[_row][_column];
}

Board::Size Board::count() const
{
    Size count = 0;

    for(Size row = 0; row < EDGE_SIZE; ++row)
    {
        for(Size col = 0; col < EDGE_SIZE; ++col)
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

    for(Size row = 0; row < EDGE_SIZE; ++row)
    {
        for(Size col = 0; col < EDGE_SIZE; ++col)
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

    for(Size row = 0; row < EDGE_SIZE; ++row)
    {
        for(Size col = 0; col < EDGE_SIZE; ++col)
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
    for(Size col = 0; col < EDGE_SIZE; ++col)
    {
        for(Size row = 0; row < EDGE_SIZE; ++row)
        {
            if(m_positions[row][col].hasNumber())
            {
                m_positions[row][col].number()->clearMergeState();
            }
        }
    }
}

Board::Array Board::status() const
{
    Array arr(EDGE_SIZE, Row(EDGE_SIZE));

    for(Size col = 0; col < EDGE_SIZE; ++col)
    {
        for(Size row = 0; row < EDGE_SIZE; ++row)
        {
            if(m_positions[row][col].hasNumber())
            {
                arr[row][col] = m_positions[row][col].number()->value();
            }
            else
            {
                arr[row][col] = 0;
            }
        }
    }

    return arr;
}

namespace
{
bool slideFromPositionToDirection(
    Position & _position,
    bool (Position::*_has_direction)() const,
    Position & (Position::*_next_direction)() const)
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

        return true;
    }

    return false;
}

Board::Size generateRandomPlace(Board::Size _limit)
{
    std::random_device                 r;
    std::default_random_engine         e(r());
    std::uniform_int_distribution<int> dist(0, _limit);

    return dist(e);
}
}
