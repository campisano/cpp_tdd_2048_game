#include "console_controller.hpp"

#include <iostream>
#include <random>
#include <termios.h>

ConsoleController::ConsoleController(
    StartGameUsecasePort & _start_usecase, MoveUsecasePort & _move_usecase)
    : m_start_usecase(_start_usecase), m_move_usecase(_move_usecase)
{
}

ConsoleController::~ConsoleController()
{
}

void ConsoleController::start()
{
    // TODO console could loop until player ask for exit or new game
    m_start_usecase.execute(2048, 3, 5);


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
        std::cout << std::endl << "make your move: ";
        std::cout.flush();
        char c, d, e;
        std::cin >> c;
        std::cin >> d;
        std::cin >> e;

        // Using 3 char type, Cause up down right left consist with 3 character
        if((c == 27) && (d == 91))
        {
            MoveUsecasePort::Direction direction;

            switch(e)
            {
            case 68:
                direction = MoveUsecasePort::Direction::left;
                m_move_usecase.execute(direction);
                break;
            case 67:
                direction = MoveUsecasePort::Direction::right;
                m_move_usecase.execute(direction);
                break;
            case 65:
                direction = MoveUsecasePort::Direction::up;
                m_move_usecase.execute(direction);
                break;
            case 66:
                direction = MoveUsecasePort::Direction::down;
                m_move_usecase.execute(direction);
                break;
            default:
                std::cout << "wrong key" << std::endl;
                break;
            }
        }
    }
}
