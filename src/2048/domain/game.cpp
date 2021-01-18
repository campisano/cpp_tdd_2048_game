#include "game.hpp"
#include <random>
#include <stdexcept>

namespace
{
inline Number::Value generateRandomValue()
{
    std::random_device                 r;
    std::default_random_engine         e(r());
    std::uniform_int_distribution<int> dist(0, 5);
    if(dist(e) < 4)
    {
        return 2;
    }
    else
    {
        return 4;
    }
}
}

Game::Game(
    Score _win_score,
    Board::Movable & _board,
    Player::Movable & _player,
    Observer::Movable & _observer)
{
    if(_win_score <= 0)
    {
        throw std::runtime_error("win_score must be positive");
    }

    m_win_score = _win_score;
    m_board     = std::move(_board);
    m_player    = std::move(_player);
    m_observer  = std::move(_observer);
}

Game::~Game()
{
}

void Game::start()
{
    notifyStart();

    do
    {
        auto num = this->generateRandomNumber();
        auto value = num->value();
        m_board->placeNumberRandomly(num);

        notifyNumberPlaced(value);

        auto direction = m_player->chooseDirection();
        m_board->slide(direction);

        notifySlide(direction);
    }
    while(! isOver());

    notifyEnd();
}

bool Game::isOver() const
{
    return playerWin() || playerLose();
}

bool Game::playerWin() const
{
    return playerScore() >= m_win_score;
}

bool Game::playerLose() const
{
    return (! playerWin()) && (! m_board->canSlide());
}

Score Game::playerScore() const
{
    return m_board->getMaxNumber();
}

void Game::notifyStart()
{
    m_observer->notifyStart(m_board->status());
}

void Game::notifyNumberPlaced(Number::Value _number)
{
    m_observer->notifyNumberPlaced(_number, m_board->status());
}

void Game::notifySlide(Direction _direction)
{
    m_observer->notifySlide(_direction, m_board->status());
}

void Game::notifyEnd()
{
    m_observer->notifyEnd(playerWin(), playerScore());
}

Number::Movable Game::generateRandomNumber()
{
    return Number::make(generateRandomValue());
}
