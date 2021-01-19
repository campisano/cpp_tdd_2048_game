#include <iostream>
#include <random>
#include <stdexcept>
#include "2048/domain/game.hpp"

namespace
{
class GameTestable : public Game
{
public:
    GameTestable(
        Board::Movable & _board,
        Player::Movable & _player,
        Observer::Movable & _observer):
        Game(2048, _board, _player, _observer)
    {
    }

    Number::Movable generateRandomNumber()
    {
        return Game::generateRandomNumber();
    }
};

class PlayerTestable : public Player
{
public:
    Direction chooseDirection()
    {
        std::random_device                 r;
        std::default_random_engine         e(r());
        std::uniform_int_distribution<int> dist(0, 3);

        switch(dist(e))
        {
        case 0:
            return Direction::left;
        case 1:
            return Direction::right;
        case 2:
            return Direction::up;
        case 3:
            return Direction::down;
        }

        throw std::runtime_error("algorithm fault");
    }
};

class ObserverTestable : public Observer
{
public:
    void notifyStart(Board::Array _board)
    {
        std::cout << "game start" << std::endl;
        print(_board);
    }

    void notifyNumberPlaced(Number::Value _number, Board::Array _board)
    {
        std::cout << "number added: " << _number << std::endl;
        print(_board);
    }

    void notifySlide(Direction _direction, Board::Array _board)
    {
        std::cout << "player slide at: " << _direction << std::endl;
        print(_board);
    }

    void notifyEnd(bool player_win, Score player_score)
    {
        if(player_win)
        {
            std::cout << "player wins with score " << player_score << std::endl;
        }
        else
        {
            std::cout << "game over..." << std::endl;
        }
    }

private:
    void print(Board::Array & _board)
    {
        for(auto row = _board.begin(); row != _board.end(); ++row)
        {
            for(auto col = row->begin(); col != row->end(); ++col)
            {
                std::cout << ' ' << * col;
            }

            std::cout << std::endl;
        }

        std::cout << std::endl;
    }
};
}

int main(int, char **)
{
    try
    {
        Board      *      board = new Board();
        Board::Movable    b(board);
        PlayerTestable  * player = new PlayerTestable();
        Player::Movable   p(player);
        Observer::Movable o(new ObserverTestable());
        GameTestable      game(b, p, o);

        game.start();
    }
    catch(std::exception const & _ex)
    {
        std::cerr << "Error: " << _ex.what() << std::endl;
        throw;
    }

    return EXIT_SUCCESS;
}
