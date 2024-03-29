#ifndef BOARD_TESTABLE__HPP__
#define BOARD_TESTABLE__HPP__

#include <vector>
#include "../../../2048/domain/board.hpp"

class BoardTestable : public Board
{
public:
    BoardTestable(Size _rows, Size _cols) : Board(_rows, _cols)
    {
    }

    Position & at(Size _row, Size _col)
    {
        return Board::at(_row, _col);
    }

    void fill(std::vector<std::vector<Number::Value>> _numbers)
    {
        auto p_row = & at(0, 0);
        auto p_col = p_row;

        for(auto row = _numbers.begin(); row != _numbers.end(); ++row)
        {
            for(auto col = row->begin(); col != row->end(); ++col)
            {
                if((*col) != 0)
                {
                    auto n = Number::make(*col);
                    p_col->place(n);
                }

                if(p_col->hasRight())
                {
                    p_col = & p_col->right();
                }
            }

            if(p_row->hasDown())
            {
                p_row = & p_row->down();
                p_col = p_row;
            }
        }
    }
};

#endif
