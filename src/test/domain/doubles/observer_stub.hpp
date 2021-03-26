#ifndef OBSERVER_STUB__HPP__
#define OBSERVER_STUB__HPP__

#include <memory>
#include "../../../2048/domain/observer.hpp"

class ObserverStub : public Observer
{
public:
    using Movable = std::unique_ptr<Observer>;

    void notifyStart(Score, Board::Size, Board::Size, Board::Array) {}
    void notifyNumberPlaced(Number::Value, Board::Array) {}
    void notifySlide(Direction, Board::Array) {}
    void notifyEnd(bool, Score) {}
};

#endif
