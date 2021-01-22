#include <iostream>
#include <random>
#include <stdexcept>
#include "2048/domain/game.hpp"

namespace
{
class PlayerFake : public Player
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

class ObserverFake : public Observer
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
        Player      *     player = new PlayerFake();
        Player::Movable   p(player);
        Observer::Movable o(new ObserverFake());
        Game              game(2048, b, p, o);

        game.start();
    }
    catch(std::exception const & _ex)
    {
        std::cerr << "Error: " << _ex.what() << std::endl;
        throw;
    }

    return EXIT_SUCCESS;
}
