#ifndef OBSERVER_SPY__HPP__
#define OBSERVER_SPY__HPP__

#include <condition_variable>
#include <mutex>
#include "../../../2048/domain/observer.hpp"

class ObserverSpy : public Observer
{
public:
    int          notifyStart_calls = 0;
    Score        notifyStart_in1;
    Board::Size  notifyStart_in2;
    Board::Size  notifyStart_in3;
    Board::Array notifyStart_in4;
    void notifyStart(
        Score _in1, Board::Size _in2, Board::Size _in3, Board::Array _in4)
    {
        ++notifyStart_calls;
        notifyStart_in1 = _in1;
        notifyStart_in2 = _in2;
        notifyStart_in3 = _in3;
        notifyStart_in4 = _in4;
    }

    int           notifyNumberPlaced_calls = 0;
    Number::Value notifyNumberPlaced_in1;
    void notifyNumberPlaced(Number::Value _in1, Board::Array)
    {
        ++notifyNumberPlaced_calls;
        notifyNumberPlaced_in1 = _in1;
    }

    int notifySlide_calls = 0;
    void notifySlide(Direction, Board::Array)
    {
        ++notifySlide_calls;
    }

    int notifyEnd_calls = 0;
    void notifyEnd(bool, Score)
    {
        {
            std::lock_guard<std::mutex> lock(m_mutex);
            ++notifyEnd_calls;
        }
        m_condition.notify_one();
    }

    void waitUtilNotifyEnd()
    {
        std::unique_lock<std::mutex> lock(m_mutex);
        m_condition.wait(lock, [this] { return notifyEnd_calls != 0; });
    }

private:
    std::mutex              m_mutex;
    std::condition_variable m_condition;
};

#endif
