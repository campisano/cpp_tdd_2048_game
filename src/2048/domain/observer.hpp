#ifndef OBSERVER__HPP__
#define OBSERVER__HPP__

#include "board.hpp"
#include "direction.hpp"
#include "score.hpp"

class Observer
{
public:
    virtual ~Observer() = default;

    virtual void notifyStart(
        Score _win_score,
        Board::Size _rows,
        Board::Size _cols,
        Board::Array _board) = 0;
    virtual void notifyNumberPlaced(Number::Value _number, Board::Array _board) = 0;
    virtual void notifySlide(Direction _direction, Board::Array _board) = 0;
    virtual void notifyEnd(bool _player_win, Score _player_score) = 0;
};

#endif
