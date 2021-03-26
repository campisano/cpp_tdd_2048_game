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
    using Movable = std::unique_ptr<Game>;

    static Movable make(
        Score      &     _win_score,
        Board::Movable & _board,
        Player     &     _player,
        Observer    &    _observer)
    {
        return Movable(new Game(_win_score, _board, _player, _observer));
    }

    virtual ~Game();

    void start();

protected:
    explicit Game(
        Score            _win_score,
        Board::Movable & _board,
        Player     &     _player,
        Observer    &    _observer);

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
    Player         &        m_player;
    Observer        &       m_observer;
};

#endif
