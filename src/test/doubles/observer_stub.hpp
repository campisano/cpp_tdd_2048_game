#ifndef OBSERVER_STUB__HPP__
#define OBSERVER_STUB__HPP__

#include "../../2048/domain/observer.hpp"

class ObserverStub : public Observer
{
public:
    void notifyStart(Board::Array) {}
    void notifyNumberPlaced(Number::Value, Board::Array) {}
    void notifySlide(Direction, Board::Array) {}
    void notifyEnd(bool, Score) {}
};

#endif
