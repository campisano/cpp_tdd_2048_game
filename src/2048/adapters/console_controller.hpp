#ifndef CONSOLE_CONTROLLER__HPP__
#define CONSOLE_CONTROLLER__HPP__

#include "../../common/move_only.hpp"
#include "../application/ports/in/move_usecase_port.hpp"
#include "../application/ports/in/start_game_usecase_port.hpp"

class ConsoleController: MoveOnly
{
public:
    ConsoleController(
        StartGameUsecasePort & _start_usecase,
        MoveUsecasePort & _move_usecase);
    virtual ~ConsoleController();

    void start();

private:
    StartGameUsecasePort & m_start_usecase;
    MoveUsecasePort    &   m_move_usecase;
};

#endif
