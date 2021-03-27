#include "console_observer.hpp"

#include <iostream>
#include <stdexcept>

namespace
{
std::ostream & operator<<(std::ostream & _out, const Direction _direction);
}

ConsoleObserver::~ConsoleObserver()
{
}

void ConsoleObserver::notifyStart(
    Score, Board::Size, Board::Size, Board::Array _board)
{
    std::cout << "game start" << std::endl;
    print(_board);
}

void ConsoleObserver::notifyNumberPlaced(
    Number::Value _number, Board::Array _board)
{
    std::cout << "number added: " << _number << std::endl;
    print(_board);
}

void ConsoleObserver::notifySlide(Direction _direction, Board::Array _board)
{
    std::cout << "player slide at: " << _direction << std::endl;
    print(_board);
}

void ConsoleObserver::notifyEnd(bool _player_win, Score _player_score)
{
    if(_player_win)
    {
        std::cout << "player wins with score " << _player_score << std::endl;
    }
    else
    {
        std::cout << "game over..." << std::endl;
    }
}

void ConsoleObserver::print(Board::Array & _board)
{
    for(auto row = _board.begin(); row != _board.end(); ++row)
    {
        for(auto col = row->begin(); col != row->end(); ++col)
        {
            if(* col != 0)
            {
                std::cout << '\t' << * col;
            }
            else
            {
                std::cout << '\t' << '.';
            }
        }

        std::cout << std::endl << std::endl;
    }

    std::cout << std::endl;
}

namespace
{
std::ostream & operator<<(std::ostream & _out, const Direction _direction)
{
    switch(_direction)
    {
    case Direction::left:
        return _out << "left";
    case Direction::right:
        return _out << "right";
    case Direction::up:
        return _out << "up";
    case Direction::down:
        return _out << "down";
    }

    throw std::runtime_error("algorithm fault");
}
}
