#ifndef GAME__HPP__
#define GAME__HPP__

#include <cstdint>
#include "board.hpp"
#include "number.hpp"

class Game
{
public:
    explicit Game();
    Game(const Game &) = delete;
    Game(Game &&) = default;
    virtual ~Game();

    Game & operator=(const Game &) = delete;
    Game & operator=(Game &&) = default;

protected:
    Number::Movable generateRandomNumber();

private:
    Board m_board;
};

#endif
