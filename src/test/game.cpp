#include "testutils.hpp"
#include "doubles/board_testable.hpp"
#include "doubles/game_testable.hpp"
#include "doubles/player_spy.hpp"
#include "doubles/observer_stub.hpp"

TEST_GROUP(GameTest) {};

TEST(GameTest, GenerateRandomNumber)
{
    Board::Movable    board(new Board());
    Player::Movable   player(new PlayerSpy());
    Observer::Movable observer(new ObserverStub());
    GameTestable      game(1, board, player, observer);

    for(int i = 0; i < 100; ++i)
    {
        auto number = game.generateRandomNumber()->value();
        CHECK_TRUE(2 == number || 4 == number);
    }
}

TEST(GameTest, PlaceNumberAfterStart)
{
    Board      *      board = new Board();
    Board::Movable    b(board);
    Player::Movable   player(new PlayerSpy());
    Observer::Movable observer(new ObserverStub());
    GameTestable      game(1, b, player, observer);

    game.start();

    CHECK_EQUAL(1, board->count());
}

TEST(GameTest, QueryPlayerSlideAfterStart)
{
    BoardTestable  *  board = new BoardTestable();
    board->fill(
    {
        { 8, 8, 0, 0 },
        { 0, 0, 0, 0 },
        { 0, 0, 0, 0 },
        { 0, 0, 0, 0 }
    });
    Board::Movable    b(board);
    PlayerSpy    *    player = new PlayerSpy();
    player->chooseDirection_out = Direction::left;
    Player::Movable   p(player);
    Observer::Movable observer(new ObserverStub());
    GameTestable      game(16, b, p, observer);

    game.start();

    CHECK_EQUAL(1, player->chooseDirection_calls);
}

TEST(GameTest, GameEndWhenWin)
{
    BoardTestable  *  board  = new BoardTestable();
    board->fill(
    {
        {    0,    0, 0, 0 },
        {    0,    0, 0, 0 },
        { 1024, 1024, 0, 0 },
        {    0,    0, 0, 0 }
    });
    PlayerSpy    *    player = new PlayerSpy();
    player->chooseDirection_out = Direction::left;
    Board::Movable    b(board);
    Player::Movable   p(player);
    Observer::Movable observer(new ObserverStub());
    GameTestable      game(2048, b, p, observer);

    game.turn();

    CHECK_EQUAL(true,  game.playerWin());
    CHECK_EQUAL(false, game.playerLose());
    CHECK_EQUAL(1, player->chooseDirection_calls);
}

TEST(GameTest, GameEndWhenLose)
{
    BoardTestable  *  board = new BoardTestable();
    board->fill(
    {
        { 16, 32, 16, 32 },
        { 32, 16, 32, 16 },
        { 16, 32, 16, 32 },
        {  0, 32, 16, 32 }
    });
    PlayerSpy    *    player = new PlayerSpy();
    player->chooseDirection_out = Direction::left;
    Board::Movable    b(board);
    Player::Movable   p(player);
    Observer::Movable observer(new ObserverStub());
    GameTestable      game(2048, b, p, observer);

    game.turn();

    CHECK_EQUAL(true,  game.playerLose());
    CHECK_EQUAL(false, game.playerWin());
    CHECK_EQUAL(1, player->chooseDirection_calls);
}
