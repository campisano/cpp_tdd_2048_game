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

Game::Game(Score _win_score, Board::Movable & _board, Player::Movable & _player)
{
    if(_win_score <= 0)
    {
        throw std::runtime_error("win_score must be positive");
    }

    m_win_score = _win_score;
    m_board = std::move(_board);
    m_player = std::move(_player);
}

Game::~Game()
{
}

void Game::start()
{
    do
    {
        auto num = this->generateRandomNumber();
        m_board->placeNumberRandomly(num);

        auto direction = m_player->makeSlide();
        if(direction == Direction::left)
        {
            m_board->slideLeft();
        }
    }
    while(! isOver());

}

bool Game::isOver() const
{
    return playerWin() || playerLose();
}

bool Game::playerWin() const
{
    return m_board->getMaxNumber() >= m_win_score;
}

bool Game::playerLose() const
{
    return (! playerWin()) && (! m_board->canSlide());
}

Number::Movable Game::generateRandomNumber()
{
    return Number::make(generateRandomValue());
}
