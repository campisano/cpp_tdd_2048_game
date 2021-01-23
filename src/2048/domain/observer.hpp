#ifndef OBSERVER__HPP__
#define OBSERVER__HPP__

#include <memory>
#include "../../common/move_only.hpp"
#include "board.hpp"
#include "direction.hpp"
#include "score.hpp"

class Observer : MoveOnly
{
public:
    using Movable = std::unique_ptr<Observer>;

    virtual ~Observer() = default;

    virtual void notifyStart(Board::Array _board) = 0;
    virtual void notifyNumberPlaced(Number::Value _number, Board::Array _board) = 0;
    virtual void notifySlide(Direction _direction, Board::Array _board) = 0;
    virtual void notifyEnd(bool player_win, Score player_score) = 0;
};

#endif
