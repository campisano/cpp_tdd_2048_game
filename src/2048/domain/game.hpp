#ifndef GAME__HPP__
#define GAME__HPP__

#include "board.hpp"
#include "number.hpp"
#include "observer.hpp"
#include "player.hpp"
#include "score.hpp"

class Game
{
public:
    explicit Game(
        Score               _win_score,
        Board::Movable   &  _board,
        Player::Movable  &  _player,
        Observer::Movable & _observer);
    Game(const Game &) = delete;
    Game(Game &&)      = default;
    virtual ~Game();

    Game & operator=(const Game &) = delete;
    Game & operator=(Game &&)      = default;

    void start();

    bool  isOver()      const;
    bool  playerWin()   const;
    bool  playerLose()  const;
    Score playerScore() const;

protected:
    Number::Movable generateRandomNumber();

private:
    void notifyStart();
    void notifyNumberPlaced(Number::Value);
    void notifySlide(Direction _direction);
    void notifyEnd();

    Score             m_win_score;
    Board::Movable    m_board;
    Player::Movable   m_player;
    Observer::Movable m_observer;
};

#endif
