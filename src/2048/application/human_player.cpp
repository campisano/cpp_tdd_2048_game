#include "human_player.hpp"

HumanPlayer::Movable HumanPlayer::make()
{
    return Movable(new HumanPlayer());
}

HumanPlayer::HumanPlayer()
    : m_direction(nullptr)
{
}

HumanPlayer::~HumanPlayer()
{
}

Direction HumanPlayer::chooseDirection()
{
    std::unique_lock<std::mutex> lock(m_mutex);
    m_condition.wait(lock, [this] { return m_direction != nullptr; });

    Direction direction = * m_direction;
    delete m_direction;
    m_direction = nullptr;

    return direction;
}

void HumanPlayer::setNextMove(Direction & _direction)
{
    {
        // block where lock_guard lives
        std::lock_guard<std::mutex> lock(m_mutex);
        m_direction = new Direction();
        *m_direction = _direction;
    }

    m_condition.notify_one();
}
