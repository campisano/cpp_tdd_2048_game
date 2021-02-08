#include "game.hpp"
#include <random>
#include <stdexcept>

Game::Game(
    Score            _win_score,
    Board::Movable & _board,
    Player     &     _player,
    Observer    &    _observer) :
    m_win_score(_win_score),
    m_board(std::move(_board)),
    m_player(_player),
    m_observer(_observer)
{
    if(m_win_score <= 0)
    {
        throw std::runtime_error("win_score must be positive");
    }
}

Game::~Game()
{
}

void Game::start()
{
    notifyStart();

    placeNumber();

    while(! isOver())
    {
        turn();
    }

    notifyEnd();
}

void Game::placeNumber()
{
    auto num   = generateRandomNumber();
    auto value = num->value();
    m_board->placeNumberRandomly(num);

    notifyNumberPlaced(value);
}

void Game::turn()
{
    requestValidSlide();

    if(! playerWin())
    {
        placeNumber();
    }
}

void Game::requestValidSlide()
{
    bool valid_slide;

    do
    {
        auto direction = m_player.chooseDirection();
        valid_slide    = m_board->slide(direction);
        notifySlide(direction);
    }
    while(! valid_slide);
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
    m_observer.notifyStart(m_board->status());
}

void Game::notifyNumberPlaced(Number::Value _number)
{
    m_observer.notifyNumberPlaced(_number, m_board->status());
}

void Game::notifySlide(Direction _direction)
{
    m_observer.notifySlide(_direction, m_board->status());
}

void Game::notifyEnd()
{
    m_observer.notifyEnd(playerWin(), playerScore());
}

Number::Movable Game::generateRandomNumber() const
{
    std::random_device                 r;
    std::default_random_engine         e(r());
    std::uniform_int_distribution<int> dist(0, 5);

    if(dist(e) < 4)
    {
        return Number::make(2);
    }
    else
    {
        return Number::make(4);
    }
}
