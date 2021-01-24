#ifndef OBSERVER_SPY__HPP__
#define OBSERVER_SPY__HPP__

#include "../../2048/domain/observer.hpp"

class ObserverSpy : public Observer
{
public:
    int  notifyStart_calls = 0;
    Board::Array notifyStart_in1;
    void notifyStart(Board::Array _in1)
    {
        ++notifyStart_calls;
        notifyStart_in1 = _in1;
    }

    int  notifyNumberPlaced_calls = 0;
    void notifyNumberPlaced(Number::Value, Board::Array)
    {
        ++notifyNumberPlaced_calls;
    }

    int  notifySlide_calls = 0;
    void notifySlide(Direction, Board::Array)
    {
        ++notifySlide_calls;
    }

    int  notifyEnd_calls = 0;
    void notifyEnd(bool, Score)
    {
        ++notifyEnd_calls;
    }
};

#endif
