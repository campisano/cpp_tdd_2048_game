#include "../testutils.hpp"

#include "../../2048/adapters/game_repository.hpp"
#include "../../2048/adapters/player_repository.hpp"
#include "../../2048/application/usecases/start_game_usecase.hpp"
#include "../domain/doubles/player_spy.hpp"
#include "../domain/doubles/observer_spy.hpp"

TEST_GROUP_BEGIN(StartGameUsecaseTest);

TEST(execute)
{
    PlayerSpy        player;
    ObserverSpy      observer;
    PlayerRepository player_repository;
    GameRepository   game_repository;
    auto             usecase = StartGameUsecase::make(
                                   game_repository,
                                   player_repository,
                                   observer);

    usecase->execute(1, 4, 5);
    observer.waitUtilNotifyEnd();

    CHECK_EQUAL(4, observer.notifyStart_in2);
    CHECK_EQUAL(5, observer.notifyStart_in3);
    CHECK_EQUAL(1, observer.notifyNumberPlaced_calls);
    CHECK_TRUE(
        2 == observer.notifyNumberPlaced_in1 ||
        4 == observer.notifyNumberPlaced_in1);
}

TEST_GROUP_END();
