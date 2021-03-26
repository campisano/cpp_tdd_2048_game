#include "../testutils.hpp"
#include "../domain/doubles/board_testable.hpp"
#include "../domain/doubles/game_testable.hpp"
#include "../domain/doubles/player_spy.hpp"
#include "../domain/doubles/observer_spy.hpp"
#include "../../2048/application/game_repository.hpp"
#include "../../2048/application/usecases/start_game_usecase.hpp"

TEST_GROUP(StartGameUsecaseTest) {};

TEST(StartGameUsecaseTest, seila)
{
    PlayerSpy::Movable   player(new PlayerSpy());
    auto obs_spy = new ObserverSpy();
    ObserverSpy::Movable observer(obs_spy);
    GameRepository       game_repository;
    auto                 usecase = StartGameUsecase::make(game_repository, * player,
                                   * observer);

    usecase->execute(1, 4, 5);

    CHECK_EQUAL(4, obs_spy->notifyStart_in2);
    CHECK_EQUAL(5, obs_spy->notifyStart_in3);
    CHECK_EQUAL(1, obs_spy->notifyNumberPlaced_calls);
    CHECK_TRUE(
        2 == obs_spy->notifyNumberPlaced_in1 ||
        4 == obs_spy->notifyNumberPlaced_in1);
}
