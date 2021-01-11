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

Game::Game(Board::Movable & _board, Score _win_score)
{
    if(_win_score <= 0)
    {
        throw std::runtime_error("win_score must be positive");
    }

    m_board = std::move(_board);
}

Game::~Game()
{
}

void Game::start()
{
    auto num = this->generateRandomNumber();
    m_board->placeNumberRandomly(num);
}

// protected

Number::Movable Game::generateRandomNumber()
{
    return Number::make(generateRandomValue());
}
