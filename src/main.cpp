#include <iostream>
#include <memory>
#include <random>
#include <stdexcept>
#include <termios.h>
#include "2048/application/usecases/start_game_usecase.hpp"
#include "test/domain/doubles/game_testable.hpp"

namespace
{
class PlayerFake : public Player
{
public:
    using Movable = std::unique_ptr<PlayerFake>;

    Direction chooseDirection()
    {
        while(true)
        {
            // from https://stackoverflow.com/a/42334773

            const int STDIN_FILENO = 0;
            // Black magic to prevent Linux from buffering keystrokes.
            struct termios t;
            tcgetattr(STDIN_FILENO, &t);
            t.c_lflag &= ~ICANON;
            tcsetattr(STDIN_FILENO, TCSANOW, &t);

            // Once the buffering is turned off, the rest is simple.
            std::cout << "make your move: ";
            std::cout.flush();
            char c, d, e;
            std::cin >> c;
            std::cin >> d;
            std::cin >> e;

            // Using 3 char type, Cause up down right left consist with 3 character
            if((c == 27) && (d = 91))
            {

                switch(e)
                {
                case 68:
                    return Direction::left;
                case 67:
                    return Direction::right;
                case 65:
                    return Direction::up;
                case 66:
                    return Direction::down;
                default:
                    std::cout << "wrong key" << std::endl;
                }
            }

        }
    }
};

class ObserverFake : public Observer
{
public:
    using Movable = std::unique_ptr<ObserverFake>;

    void notifyStart(
        Score, Board::Size, Board::Size, Board::Array _board)
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

    void notifyEnd(bool _player_win, Score _player_score)
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

private:
    void print(Board::Array & _board)
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
};
}

int main(int, char **)
{
    try
    {
        GameRepository        grp;
        PlayerFake::Movable   player(new PlayerFake());
        ObserverFake::Movable observer(new ObserverFake());
        auto                  usecase = StartGameUsecase::make(grp, *player, *observer);
        usecase->execute(2048, 3, 5);
    }
    catch(std::exception const & _ex)
    {
        std::cerr << "Error: " << _ex.what() << std::endl;
        throw;
    }

    return EXIT_SUCCESS;
}
