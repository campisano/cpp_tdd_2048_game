#ifndef GAME__HPP__
#define GAME__HPP__

#include "../../common/move_only.hpp"
#include "board.hpp"
#include "direction.hpp"
#include "number.hpp"
#include "observer.hpp"
#include "player.hpp"
#include "score.hpp"

class Game : MoveOnly
{
public:
    explicit Game(
        Score               _win_score,
        Board::Movable   &  _board,
        Player::Movable  &  _player,
        Observer::Movable & _observer);
    virtual ~Game();

    void start();

protected:
    bool  isOver()      const;
    bool  playerWin()   const;
    bool  playerLose()  const;
    Score playerScore() const;

    void turn();
    Number::Movable generateRandomNumber() const;

private:
    void placeNumber();
    void requestValidSlide();

    void notifyStart();
    void notifyNumberPlaced(Number::Value);
    void notifySlide(Direction _direction);
    void notifyEnd();

    const Score             m_win_score;
    const Board::Movable    m_board;
    const Player::Movable   m_player;
    const Observer::Movable m_observer;
};

#endif
