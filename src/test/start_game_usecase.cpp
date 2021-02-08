#include "testutils.hpp"
#include "doubles/board_testable.hpp"
#include "doubles/game_testable.hpp"

#include "doubles/player_spy.hpp"
#include "doubles/observer_spy.hpp"

namespace
{

class GameRepository
{
public:
    Game::Movable create(
        Score      &     _win_score,
        Board::Movable & _board,
        Player     &     _player,
        Observer    &    _observer)
    {
        return Game::make(_win_score, _board, _player, _observer);
    }
};

#include "../common/move_only.hpp"

class StartNewGameUsecase : MoveOnly
{
public:
    using Movable = std::unique_ptr<StartNewGameUsecase>;
    static Movable make(GameRepository & _grp, Player & _ply, Observer & _obs)
    {
        return Movable(new StartNewGameUsecase(_grp, _ply, _obs));
    }

    explicit StartNewGameUsecase(
        GameRepository & _grp, Player & _ply, Observer & _obs):
        m_grp(_grp), m_ply(_ply), m_obs(_obs)
    {
    }

    void execute(int _score, int _rows, int _cols)
    {
        auto board = Board::make(_rows, _cols);
        auto game  = m_grp.create(_score, board, m_ply, m_obs);

        game->start();
    }

private:
    GameRepository & m_grp;
    Player     &     m_ply;
    Observer    &    m_obs;
};
}

TEST_GROUP(StartGameUsecaseTest) {};

TEST(StartGameUsecaseTest, seila)
{
    Player::Movable   player(new PlayerSpy());
    auto obs_spy = new ObserverSpy();
    Observer::Movable observer(obs_spy);
    GameRepository    game_repository;
    auto              usecase = StartNewGameUsecase::make(
                                    game_repository, * player, * observer);

    usecase->execute(1, 4, 5);

    CHECK_EQUAL(4, obs_spy->notifyStart_in2);
    CHECK_EQUAL(5, obs_spy->notifyStart_in3);
    CHECK_EQUAL(1, obs_spy->notifyNumberPlaced_calls);
    CHECK_TRUE(
        2 == obs_spy->notifyNumberPlaced_in1 ||
        4 == obs_spy->notifyNumberPlaced_in1);
}
