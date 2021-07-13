#include "board.hpp"

#include <stdexcept>
#include "../../common/random_generator.hpp"

namespace
{
bool slideFromPositionToDirection(
    Position & _position,
    bool (Position::*_has_direction)() const,
    Position & (Position::*_next_direction)() const);

Board::Size generateRandomPlace(Board::Size _limit);
}

Board::Board(Size _rows, Size _cols) : m_rows(_rows), m_cols(_cols)
{
    if(m_rows < 1)
    {
        throw std::invalid_argument("rows cannot be less than 1");
    }

    if(m_cols < 1)
    {
        throw std::invalid_argument("cols cannot be less than 1");
    }


    m_positions = new Position *[m_rows];

    for(int row = 0; row < m_rows; ++row)
    {
        m_positions[row] = new Position[m_cols];
    }

    for(Size row = 0; row < m_rows; ++row)
    {
        for(Size col = 0; col < m_cols; ++col)
        {
            if(row > 0)
            {
                m_positions[row][col].up(m_positions[row - 1][col]);
            }
            if(row < (m_rows - 1))
            {
                m_positions[row][col].down(m_positions[row + 1][col]);
            }
            if(col > 0)
            {
                m_positions[row][col].left(m_positions[row][col - 1]);
            }
            if(col < (m_cols - 1))
            {
                m_positions[row][col].right(m_positions[row][col + 1]);
            }
        }
    }
}

Board::~Board()
{
    for(Size row = 0; row < m_rows; ++row)
    {
        delete [] m_positions[row];
    }

    delete [] m_positions;
}

Board::Movable Board::make(Size _rows, Size _cols)
{
    return Movable(new Board(_rows, _cols));
}

bool Board::slide(Direction _direction)
{
    bool valid_move;

    switch(_direction)
    {
    case Direction::left:
        valid_move = slideLeft();
        break;
    case Direction::right:
        valid_move = slideRight();
        break;
    case Direction::up:
        valid_move = slideUp();
        break;
    case Direction::down:
        valid_move = slideDown();
        break;
    default:
        throw std::invalid_argument("direction unknown");
    }

    clearMergeState();

    return valid_move;
}

bool Board::slideLeft()
{
    bool any_valid_slide = false;
    bool valid_slide;

    for(Size row = 0; row < m_rows; ++row)
    {
        for(Size col = 1; col < m_cols; ++col)
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

    for(Size row = 0; row < m_rows; ++row)
    {
        for(Size col = m_cols - 2; col >= 0; --col)
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

    for(Size col = 0; col < m_cols; ++col)
    {
        for(Size row = 1; row < m_rows; ++row)
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

    for(Size col = 0; col < m_cols; ++col)
    {
        for(Size row = m_rows - 2; row >= 0; --row)
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
        throw std::out_of_range("no space left on board");
    }

    Size rand_pos = generateRandomPlace(free_pos - 1);

    for(Size row = 0; row < m_rows; ++row)
    {
        for(Size col = 0; col < m_cols; ++col)
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

    throw std::out_of_range("algorithm fault");
}

Board::Size Board::rows() const
{
    return m_rows;
}

Board::Size Board::cols() const
{
    return m_cols;
}

Board::Size Board::size() const
{
    return m_rows * m_cols;
}

Position & Board::at(Size _row, Size _col)
{
    if(
        _row < 0 || _col < 0 ||
        _row >= m_rows || _col >= m_cols)
    {
        throw std::out_of_range("out of board boundaries");
    }

    return m_positions[_row][_col];
}

Board::Size Board::count() const
{
    Size count = 0;

    for(Size row = 0; row < m_rows; ++row)
    {
        for(Size col = 0; col < m_cols; ++col)
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

    for(Size row = 0; row < m_rows; ++row)
    {
        for(Size col = 0; col < m_cols; ++col)
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

    for(Size row = 0; row < m_rows; ++row)
    {
        for(Size col = 0; col < m_cols; ++col)
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
    for(Size col = 0; col < m_cols; ++col)
    {
        for(Size row = 0; row < m_rows; ++row)
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
    Array arr(m_rows, Row(m_cols));

    for(Size col = 0; col < m_cols; ++col)
    {
        for(Size row = 0; row < m_rows; ++row)
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
    std::mt19937 & engine = RandomGenerator::instance().get();
    std::uniform_int_distribution<int> distribution(0, _limit);

    return distribution(engine);
}
}
