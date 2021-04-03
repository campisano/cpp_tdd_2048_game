#include "../testutils.hpp"

#include "../../2048/adapters/game_repository.hpp"
#include "../../2048/adapters/player_repository.hpp"
#include "../../2048/application/usecases/start_game_usecase.hpp"
#include "../domain/doubles/board_testable.hpp"
#include "../domain/doubles/game_testable.hpp"
#include "../domain/doubles/player_spy.hpp"
#include "../domain/doubles/observer_spy.hpp"

TEST_GROUP(StartGameUsecaseTest) {};

TEST(StartGameUsecaseTest, execute)
{
    PlayerSpy::Movable   player(new PlayerSpy());
    auto obs_spy = new ObserverSpy();
    ObserverSpy::Movable observer(obs_spy);
    PlayerRepository     player_repository;
    GameRepository       game_repository;
    auto                 usecase = StartGameUsecase::make(
                                       game_repository,
                                       player_repository,
                                       * observer);

    usecase->execute(1, 4, 5);
    game_repository.getCurrent().join(); // TODO really strange stuff to be placed here

    CHECK_EQUAL(4, obs_spy->notifyStart_in2);
    CHECK_EQUAL(5, obs_spy->notifyStart_in3);
    CHECK_EQUAL(1, obs_spy->notifyNumberPlaced_calls);
    CHECK_TRUE(
        2 == obs_spy->notifyNumberPlaced_in1 ||
        4 == obs_spy->notifyNumberPlaced_in1);
}
