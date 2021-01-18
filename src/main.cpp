#include <iostream>
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

    inline Number::Movable generateRandomNumber()
    {
        return Game::generateRandomNumber();
    }
};

class PlayerTestable : public Player
{
public:
    int       chooseDirection_calls = 0;
    Direction chooseDirection_out;
    inline Direction chooseDirection()
    {
        ++chooseDirection_calls;
        return chooseDirection_out;
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
        player->chooseDirection_out = Direction::left;
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
