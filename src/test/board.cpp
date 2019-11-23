#include <cstdint>
#include "testutils.hpp"
#include "../2048/domain/board.hpp"

namespace
{
const std::size_t EXPECTED_BOARD_SIZE = 16;
const Number::Value ARBITRARY_VALUE = 8;
}

TEST_GROUP(BoardTest) {};

TEST(BoardTest, Creation)
{
    Board board;
    CHECK_EQUAL(EXPECTED_BOARD_SIZE, board.size());
}

TEST(BoardTest, AtInside)
{
    Board board;
    board.at(0, 0);
    board.at(3, 3);
}

TEST(BoardTest, ThrowsOnAtUpOutside)
{
    Board board;
    CHECK_THROWS_STDEXCEPT(
        std::runtime_error, "out of board boundaries", board.at(-1, 0));
}

TEST(BoardTest, ThrowsOnAtDownOutside)
{
    Board board;
    CHECK_THROWS_STDEXCEPT(
        std::runtime_error, "out of board boundaries", board.at(4, 0));
}

TEST(BoardTest, ThrowsOnAtLeftOutside)
{
    Board board;
    CHECK_THROWS_STDEXCEPT(
        std::runtime_error, "out of board boundaries", board.at(0, -1));
}

TEST(BoardTest, ThrowsOnAtRightOutside)
{
    Board board;
    CHECK_THROWS_STDEXCEPT(
        std::runtime_error, "out of board boundaries", board.at(0, 4));
}

TEST(BoardTest, BorderUpLeft)
{
    Board board;
    CHECK_FALSE(board.at(0, 0).hasUp());
    CHECK_TRUE(board.at(0, 0).hasDown());
    CHECK_FALSE(board.at(0, 0).hasLeft());
    CHECK_TRUE(board.at(0, 0).hasRight());
}

TEST(BoardTest, BorderUpRight)
{
    Board board;
    CHECK_FALSE(board.at(0, 3).hasUp());
    CHECK_TRUE(board.at(0, 3).hasDown());
    CHECK_TRUE(board.at(0, 3).hasLeft());
    CHECK_FALSE(board.at(0, 3).hasRight());
}

TEST(BoardTest, BorderDownLeft)
{
    Board board;
    CHECK_TRUE(board.at(3, 0).hasUp());
    CHECK_FALSE(board.at(3, 0).hasDown());
    CHECK_FALSE(board.at(3, 0).hasLeft());
    CHECK_TRUE(board.at(3, 0).hasRight());
}

TEST(BoardTest, BorderDownRight)
{
    Board board;
    CHECK_TRUE(board.at(3, 3).hasUp());
    CHECK_FALSE(board.at(3, 3).hasDown());
    CHECK_TRUE(board.at(3, 3).hasLeft());
    CHECK_FALSE(board.at(3, 3).hasRight());
}

TEST(BoardTest, BorderSlideLeft)
{
    Board board;
    auto number = Number::make(ARBITRARY_VALUE);
    Number * num_ptr = number.get();
    board.at(2, 2).place(number);
    board.slideLeft();
    CHECK_FALSE(board.at(2, 2).hasNumber());
    CHECK_TRUE(board.at(2, 0).hasNumber());
    CHECK_EQUAL(num_ptr, board.at(2, 0).number().get());
}

TEST(BoardTest, BorderSlideLeftIsAppliedToAllNumbers)
{
    Board board;
    auto num_1_1 = Number::make(ARBITRARY_VALUE);
    auto num_2_2 = Number::make(ARBITRARY_VALUE);
    auto num_3_3 = Number::make(ARBITRARY_VALUE);
    board.at(1, 1).place(num_1_1);
    board.at(2, 2).place(num_2_2);
    board.at(3, 3).place(num_3_3);

    board.slideLeft();

    CHECK_FALSE(board.at(1, 1).hasNumber());
    CHECK_FALSE(board.at(2, 2).hasNumber());
    CHECK_FALSE(board.at(3, 3).hasNumber());
    CHECK_TRUE(board.at(1, 0).hasNumber());
    CHECK_TRUE(board.at(2, 0).hasNumber());
    CHECK_TRUE(board.at(3, 0).hasNumber());
}
