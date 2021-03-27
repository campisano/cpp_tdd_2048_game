#ifndef HUMAN_PLAYER__HPP__
#define HUMAN_PLAYER__HPP__

#include <condition_variable>
#include <memory>
#include <mutex>
#include "../../common/move_only.hpp"
#include "../domain/player.hpp"

class HumanPlayer: public Player, MoveOnly
{
public:
    using Movable = std::unique_ptr<HumanPlayer>;

    static Movable make();

    virtual ~HumanPlayer();

    Direction chooseDirection();

    void setNextMove(Direction & _direction);

private:
    explicit HumanPlayer();

    Direction * m_direction;

    std::mutex              m_mutex;
    std::condition_variable m_condition;
};

#endif
