#ifndef CONSOLE_OBSERVER__HPP__
#define CONSOLE_OBSERVER__HPP__

#include "../../common/move_only.hpp"
#include "../domain/observer.hpp"

//TODO consoleObserver is an adpater but knows Observer that is a domain stuff
class ConsoleObserver : public Observer, MoveOnly
{
public:
    virtual ~ConsoleObserver();

    void notifyStart(Score, Board::Size, Board::Size, Board::Array _board);
    void notifyNumberPlaced(Number::Value _number, Board::Array _board);
    void notifySlide(Direction _direction, Board::Array _board);
    void notifyEnd(bool _player_win, Score _player_score);

private:
    void print(Board::Array & _board);
};

#endif
