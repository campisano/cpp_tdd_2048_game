#ifndef GAME__HPP__
#define GAME__HPP__

#include <cstdint>
#include "board.hpp"
#include "number.hpp"
#include "player.hpp"

class Game
{
public:
    using Score = int16_t;

public:
    explicit Game(Score _win_score, Board::Movable & _board,
                  Player::Movable & _player);
    Game(const Game &) = delete;
    Game(Game &&) = default;
    virtual ~Game();

    Game & operator=(const Game &) = delete;
    Game & operator=(Game &&) = default;

    void start();

protected:
    Number::Movable generateRandomNumber();

private:
    Score m_win_score;
    Board::Movable m_board;
    Player::Movable m_player;
};

#endif
