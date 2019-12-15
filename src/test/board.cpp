#include <cstdint>
#include "testutils.hpp"
#include "../2048/domain/board.hpp"

namespace
{
const std::size_t EXPECTED_BOARD_SIZE = 16;
const Number::Value ARBITRARY_VALUE = 8;
}

TEST_GROUP(BoardTest) {};

class BoardTestable : public Board
{
public:
    virtual Position & at(uint8_t _row, uint8_t _column)
    {
        return Board::at(_row, _column);
    }
};

TEST(BoardTest, Creation)
{
    Board board;

    CHECK_EQUAL(EXPECTED_BOARD_SIZE, board.size());
}

TEST(BoardTest, AtInside)
{
    BoardTestable board;

    board.at(0, 0);
    board.at(3, 3);
}

TEST(BoardTest, ThrowsOnAtUpOutside)
{
    BoardTestable board;

    CHECK_THROWS_STDEXCEPT(
        std::runtime_error, "out of board boundaries", board.at(-1, 0));
}

TEST(BoardTest, ThrowsOnAtDownOutside)
{
    BoardTestable board;

    CHECK_THROWS_STDEXCEPT(
        std::runtime_error, "out of board boundaries", board.at(4, 0));
}

TEST(BoardTest, ThrowsOnAtLeftOutside)
{
    BoardTestable board;

    CHECK_THROWS_STDEXCEPT(
        std::runtime_error, "out of board boundaries", board.at(0, -1));
}

TEST(BoardTest, ThrowsOnAtRightOutside)
{
    BoardTestable board;

    CHECK_THROWS_STDEXCEPT(
        std::runtime_error, "out of board boundaries", board.at(0, 4));
}

TEST(BoardTest, AtEdgeUpLeft)
{
    BoardTestable board;

    CHECK_FALSE(board.at(0, 0).hasUp());
    CHECK_TRUE(board.at(0, 0).hasDown());
    CHECK_FALSE(board.at(0, 0).hasLeft());
    CHECK_TRUE(board.at(0, 0).hasRight());
}

TEST(BoardTest, AtEdgeUpRight)
{
    BoardTestable board;

    CHECK_FALSE(board.at(0, 3).hasUp());
    CHECK_TRUE(board.at(0, 3).hasDown());
    CHECK_TRUE(board.at(0, 3).hasLeft());
    CHECK_FALSE(board.at(0, 3).hasRight());
}

TEST(BoardTest, AtEdgeDownLeft)
{
    BoardTestable board;

    CHECK_TRUE(board.at(3, 0).hasUp());
    CHECK_FALSE(board.at(3, 0).hasDown());
    CHECK_FALSE(board.at(3, 0).hasLeft());
    CHECK_TRUE(board.at(3, 0).hasRight());
}

TEST(BoardTest, AtEdgeDownRight)
{
    BoardTestable board;

    CHECK_TRUE(board.at(3, 3).hasUp());
    CHECK_FALSE(board.at(3, 3).hasDown());
    CHECK_TRUE(board.at(3, 3).hasLeft());
    CHECK_FALSE(board.at(3, 3).hasRight());
}

TEST(BoardTest, SlideLeft)
{
    BoardTestable board;
    auto          number  = Number::make(ARBITRARY_VALUE);
    Number    *   num_ptr = number.get();
    board.at(2, 2).place(number);

    board.slideLeft();

    CHECK_FALSE(board.at(2, 2).hasNumber());
    CHECK_TRUE(board.at(2, 0).hasNumber());
    CHECK_EQUAL(num_ptr, board.at(2, 0).number().get());
}

TEST(BoardTest, SlideRight)
{
    BoardTestable board;
    auto          number  = Number::make(ARBITRARY_VALUE);
    Number    *   num_ptr = number.get();
    board.at(1, 1).place(number);

    board.slideRight();

    CHECK_FALSE(board.at(1, 1).hasNumber());
    CHECK_TRUE(board.at(1, 3).hasNumber());
    CHECK_EQUAL(num_ptr, board.at(1, 3).number().get());
}

TEST(BoardTest, SlideUp)
{
    BoardTestable board;
    auto          number  = Number::make(ARBITRARY_VALUE);
    Number    *   num_ptr = number.get();
    board.at(2, 2).place(number);

    board.slideUp();

    CHECK_FALSE(board.at(2, 2).hasNumber());
    CHECK_TRUE(board.at(0, 2).hasNumber());
    CHECK_EQUAL(num_ptr, board.at(0, 2).number().get());
}

TEST(BoardTest, SlideDown)
{
    BoardTestable board;
    auto          number  = Number::make(ARBITRARY_VALUE);
    Number    *   num_ptr = number.get();
    board.at(1, 1).place(number);

    board.slideDown();

    CHECK_FALSE(board.at(1, 1).hasNumber());
    CHECK_TRUE(board.at(3, 1).hasNumber());
    CHECK_EQUAL(num_ptr, board.at(3, 1).number().get());
}

TEST(BoardTest, SlideIsAppliedToAllNumbers)
{
    BoardTestable board;
    auto          num_1_1 = Number::make(ARBITRARY_VALUE);
    auto          num_2_2 = Number::make(ARBITRARY_VALUE);
    auto          num_3_3 = Number::make(ARBITRARY_VALUE);
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

TEST(BoardTest, SlideNotOverEdge)
{
    BoardTestable board;
    auto          number = Number::make(ARBITRARY_VALUE);
    board.at(2, 0).place(number);

    board.slideLeft();

    CHECK_TRUE(board.at(2, 0).hasNumber());
}

TEST(BoardTest, SlideStopOnNotMergeableNumber)
{
    BoardTestable board;
    auto          moving_number   = Number::make(ARBITRARY_VALUE);
    auto          blocking_number = Number::make(4 * ARBITRARY_VALUE);
    board.at(2, 3).place(moving_number);
    board.at(2, 0).place(blocking_number);

    board.slideLeft();

    CHECK_TRUE(board.at(2, 1).hasNumber());
    CHECK_EQUAL(ARBITRARY_VALUE, board.at(2, 1).number()->value());
    CHECK_TRUE(board.at(2, 0).hasNumber());
    CHECK_EQUAL(4 * ARBITRARY_VALUE, board.at(2, 0).number()->value());
}

TEST(BoardTest, SlideStopOnNotMergeableNumberAfterItsMove)
{
    BoardTestable board;
    auto          moving_number          = Number::make(ARBITRARY_VALUE);
    auto          moving_blocking_number = Number::make(4 * ARBITRARY_VALUE);
    board.at(2, 3).place(moving_number);
    board.at(2, 1).place(moving_blocking_number);

    board.slideLeft();

    CHECK_TRUE(board.at(2, 1).hasNumber());
    CHECK_EQUAL(ARBITRARY_VALUE, board.at(2, 1).number()->value());
    CHECK_TRUE(board.at(2, 0).hasNumber());
    CHECK_EQUAL(4 * ARBITRARY_VALUE, board.at(2, 0).number()->value());
}

TEST(BoardTest, SlideMoveAndMergeAtEdgeTwoMergeableNumbers)
{
    BoardTestable board;
    auto          moving_number  = Number::make(ARBITRARY_VALUE);
    auto          blocked_number = Number::make(ARBITRARY_VALUE);
    board.at(2, 3).place(moving_number);
    board.at(2, 1).place(blocked_number);

    board.slideLeft();

    CHECK_TRUE(board.at(2, 0).hasNumber());
    CHECK_FALSE(board.at(2, 1).hasNumber());
    CHECK_FALSE(board.at(2, 2).hasNumber());
    CHECK_FALSE(board.at(2, 3).hasNumber());
    CHECK_EQUAL(2 * ARBITRARY_VALUE, board.at(2, 0).number()->value());
}

TEST(BoardTest, SlideNotMergeThirdMergeableNumber)
{
    BoardTestable board;
    auto          moving_number         = Number::make(2 * ARBITRARY_VALUE);
    Number    *   moving_num_ptr        = moving_number.get();
    auto          moving_merging_number = Number::make(ARBITRARY_VALUE);
    auto          blocked_number        = Number::make(ARBITRARY_VALUE);
    board.at(2, 2).place(moving_number);
    board.at(2, 1).place(moving_merging_number);
    board.at(2, 0).place(blocked_number);

    board.slideLeft();

    CHECK_TRUE(board.at(2, 0).hasNumber());
    CHECK_TRUE(board.at(2, 1).hasNumber());
    CHECK_FALSE(board.at(2, 2).hasNumber());
    CHECK_FALSE(board.at(2, 3).hasNumber());
    CHECK_EQUAL(2 * ARBITRARY_VALUE, board.at(2, 0).number()->value());
    CHECK_EQUAL(2 * ARBITRARY_VALUE, board.at(2, 1).number()->value());
    CHECK_EQUAL(moving_num_ptr, board.at(2, 1).number().get());
}

TEST(BoardTest, SlideMergeTwoByTwoOfFourEqualNumbers)
{
    BoardTestable board;
    auto          num_0 = Number::make(ARBITRARY_VALUE);
    auto          num_1 = Number::make(ARBITRARY_VALUE);
    auto          num_2 = Number::make(ARBITRARY_VALUE);
    auto          num_3 = Number::make(ARBITRARY_VALUE);
    board.at(2, 0).place(num_0);
    board.at(2, 1).place(num_1);
    board.at(2, 2).place(num_2);
    board.at(2, 3).place(num_3);

    board.slideLeft();

    CHECK_TRUE(board.at(2, 0).hasNumber());
    CHECK_TRUE(board.at(2, 1).hasNumber());
    CHECK_FALSE(board.at(2, 2).hasNumber());
    CHECK_FALSE(board.at(2, 3).hasNumber());
    CHECK_EQUAL(2 * ARBITRARY_VALUE, board.at(2, 0).number()->value());
    CHECK_EQUAL(2 * ARBITRARY_VALUE, board.at(2, 1).number()->value());
}

TEST(BoardTest, SlideMergeCouplesOfMergeableNumbers)
{
    BoardTestable board;
    auto          num_0 = Number::make(ARBITRARY_VALUE);
    auto          num_1 = Number::make(ARBITRARY_VALUE);
    auto          num_2 = Number::make(2 * ARBITRARY_VALUE);
    auto          num_3 = Number::make(2 * ARBITRARY_VALUE);
    board.at(2, 0).place(num_0);
    board.at(2, 1).place(num_1);
    board.at(2, 2).place(num_2);
    board.at(2, 3).place(num_3);

    board.slideLeft();

    CHECK_TRUE(board.at(2, 0).hasNumber());
    CHECK_TRUE(board.at(2, 1).hasNumber());
    CHECK_FALSE(board.at(2, 2).hasNumber());
    CHECK_FALSE(board.at(2, 3).hasNumber());
    CHECK_EQUAL(2 * ARBITRARY_VALUE, board.at(2, 0).number()->value());
    CHECK_EQUAL(4 * ARBITRARY_VALUE, board.at(2, 1).number()->value());
}

TEST(BoardTest, SlideMergeMiddleNumbers)
{
    BoardTestable board;
    auto          num_0 = Number::make(ARBITRARY_VALUE);
    auto          num_1 = Number::make(2 * ARBITRARY_VALUE);
    auto          num_2 = Number::make(2 * ARBITRARY_VALUE);
    auto          num_3 = Number::make(4 * ARBITRARY_VALUE);
    board.at(2, 0).place(num_0);
    board.at(2, 1).place(num_1);
    board.at(2, 2).place(num_2);
    board.at(2, 3).place(num_3);

    board.slideLeft();

    CHECK_TRUE(board.at(2, 0).hasNumber());
    CHECK_TRUE(board.at(2, 1).hasNumber());
    CHECK_TRUE(board.at(2, 2).hasNumber());
    CHECK_FALSE(board.at(2, 3).hasNumber());
    CHECK_EQUAL(ARBITRARY_VALUE, board.at(2, 0).number()->value());
    CHECK_EQUAL(4 * ARBITRARY_VALUE, board.at(2, 1).number()->value());
    CHECK_EQUAL(4 * ARBITRARY_VALUE, board.at(2, 2).number()->value());
}
