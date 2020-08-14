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

Game::Game()
{
}

Game::~Game()
{
}

// protected

Number::Movable Game::generateRandomNumber()
{
    return Number::make(generateRandomValue());
}
