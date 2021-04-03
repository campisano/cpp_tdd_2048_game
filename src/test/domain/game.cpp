#include "../testutils.hpp"

#include "doubles/board_testable.hpp"
#include "doubles/game_testable.hpp"
#include "doubles/player_spy.hpp"
#include "doubles/observer_spy.hpp"

TEST_GROUP(GameTest) {};

TEST(GameTest, GenerateRandomNumber)
{
    auto         mov_board = Board::make(4, 4);
    PlayerSpy    player;
    ObserverSpy  observer;
    GameTestable game(1, mov_board, player, observer);

    for(int i = 0; i < 100; ++i)
    {
        auto number = game.generateRandomNumber()->value();
        CHECK_TRUE(2 == number || 4 == number);
    }
}

TEST(GameTest, PlaceNumberAfterStart)
{
    auto           board = new BoardTestable(4, 4);
    Board::Movable mov_board(board);
    PlayerSpy      player;
    ObserverSpy    observer;
    GameTestable   game(1, mov_board, player, observer);

    game.start();

    CHECK_EQUAL(1, board->count());
}

TEST(GameTest, QueryPlayerSlideAfterStart)
{
    auto board = new BoardTestable(4, 4);
    board->fill(
    {
        { 8, 8, 0, 0 },
        { 0, 0, 0, 0 },
        { 0, 0, 0, 0 },
        { 0, 0, 0, 0 }
    });
    Board::Movable mov_board(board);
    PlayerSpy      player;
    player.chooseDirection_out = Direction::left;
    ObserverSpy    observer;
    GameTestable   game(16, mov_board, player, observer);

    game.start();

    CHECK_EQUAL(1, player.chooseDirection_calls);
}

TEST(GameTest, GameEndWhenWin)
{
    auto board = new BoardTestable(4, 4);
    board->fill(
    {
        {    0,    0, 0, 0 },
        {    0,    0, 0, 0 },
        { 1024, 1024, 0, 0 },
        {    0,    0, 0, 0 }
    });
    PlayerSpy      player;
    player.chooseDirection_out = Direction::left;
    Board::Movable mov_board(board);
    ObserverSpy    observer;
    GameTestable   game(2048, mov_board, player, observer);

    game.turn();

    CHECK_EQUAL(true,  game.playerWin());
    CHECK_EQUAL(false, game.playerLose());
    CHECK_EQUAL(1, player.chooseDirection_calls);
}

TEST(GameTest, GameEndWhenLose)
{
    auto board = new BoardTestable(4, 4);
    board->fill(
    {
        { 16, 32, 16, 32 },
        { 32, 16, 32, 16 },
        { 16, 32, 16, 32 },
        {  0, 32, 16, 32 }
    });
    PlayerSpy      player;
    player.chooseDirection_out = Direction::left;
    Board::Movable mov_board(board);
    ObserverSpy    observer;
    GameTestable   game(2048, mov_board, player, observer);

    game.turn();

    CHECK_EQUAL(true,  game.playerLose());
    CHECK_EQUAL(false, game.playerWin());
    CHECK_EQUAL(1, player.chooseDirection_calls);
}

TEST(GameTest, NotifyStart)
{
    auto         mov_board = Board::make(4, 4);
    PlayerSpy    player;
    ObserverSpy  observer;
    GameTestable game(1, mov_board, player, observer);

    game.start();

    CHECK_EQUAL(1, observer.notifyStart_calls);
    CHECK_TRUE(
        std::vector<std::vector<Number::Value>>(
    {
        { 0, 0, 0, 0 },
        { 0, 0, 0, 0 },
        { 0, 0, 0, 0 },
        { 0, 0, 0, 0 }
    }) == observer.notifyStart_in4)
}

TEST(GameTest, NotifyPlaceNumber)
{
    auto         mov_board = Board::make(4, 4);
    PlayerSpy    player;
    ObserverSpy  observer;
    GameTestable game(1, mov_board, player, observer);

    game.start();

    CHECK_EQUAL(1, observer.notifyNumberPlaced_calls);
}

TEST(GameTest, NotifySlide)
{
    auto board = new BoardTestable(4, 4);
    board->fill(
    {
        {    0,    0, 0, 0 },
        {    0,    0, 0, 0 },
        { 1024, 1024, 0, 0 },
        {    0,    0, 0, 0 }
    });
    PlayerSpy      player;
    player.chooseDirection_out = Direction::left;
    Board::Movable mov_board(board);
    ObserverSpy    observer;
    GameTestable   game(2048, mov_board, player, observer);

    game.start();

    CHECK_EQUAL(1, observer.notifySlide_calls);
}

TEST(GameTest, NotifyEnd)
{
    auto         mov_board = Board::make(4, 4);
    PlayerSpy    player;
    ObserverSpy  observer;
    GameTestable game(1, mov_board, player, observer);

    game.start();

    CHECK_EQUAL(1, observer.notifyEnd_calls);
}
