#include "testutils.hpp"
#include "doubles/board_testable.hpp"

namespace
{
const Board::Size   EXPECTED_BOARD_SIZE = 16;
const Number::Value ARBITRARY_VALUE     = 8;
}

TEST_GROUP(BoardTest) {};

TEST(BoardTest, Creation)
{
    BoardTestable board;

    CHECK_EQUAL(EXPECTED_BOARD_SIZE, board.size());
    CHECK_EQUAL(0, board.count());
}

TEST(BoardTest, AtInside)
{
    BoardTestable board;

    board.at(0, 0);
    board.at(3, 3);
}

// TODO -1 unsigned became int.max -1 so the test break but for luck
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
    auto          num_ptr = number.get();
    board.at(2, 2).place(number);

    board.slide(Direction::left);

    CHECK_FALSE(board.at(2, 2).hasNumber());
    CHECK_TRUE(board.at(2, 0).hasNumber());
    CHECK_EQUAL(num_ptr, board.at(2, 0).number().get());
}

TEST(BoardTest, SlideRight)
{
    BoardTestable board;
    auto          number  = Number::make(ARBITRARY_VALUE);
    auto          num_ptr = number.get();
    board.at(1, 1).place(number);

    board.slide(Direction::right);

    CHECK_FALSE(board.at(1, 1).hasNumber());
    CHECK_TRUE(board.at(1, 3).hasNumber());
    CHECK_EQUAL(num_ptr, board.at(1, 3).number().get());
}

TEST(BoardTest, SlideUp)
{
    BoardTestable board;
    auto          number  = Number::make(ARBITRARY_VALUE);
    auto          num_ptr = number.get();
    board.at(2, 2).place(number);

    board.slide(Direction::up);

    CHECK_FALSE(board.at(2, 2).hasNumber());
    CHECK_TRUE(board.at(0, 2).hasNumber());
    CHECK_EQUAL(num_ptr, board.at(0, 2).number().get());
}

TEST(BoardTest, SlideDown)
{
    BoardTestable board;
    auto          number  = Number::make(ARBITRARY_VALUE);
    auto          num_ptr = number.get();
    board.at(1, 1).place(number);

    board.slide(Direction::down);

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

    board.slide(Direction::left);

    CHECK_FALSE(board.at(1, 1).hasNumber());
    CHECK_FALSE(board.at(2, 2).hasNumber());
    CHECK_FALSE(board.at(3, 3).hasNumber());
    CHECK_TRUE(board.at(1, 0).hasNumber());
    CHECK_TRUE(board.at(2, 0).hasNumber());
    CHECK_TRUE(board.at(3, 0).hasNumber());
}

TEST(BoardTest, SlideNotOverBoardEdge)
{
    BoardTestable board;
    auto          number = Number::make(ARBITRARY_VALUE);
    board.at(2, 0).place(number);

    board.slide(Direction::left);

    CHECK_TRUE(board.at(2, 0).hasNumber());
}

TEST(BoardTest, SlideStopOnNotMergeableNumber)
{
    BoardTestable board;
    auto          moving_number   = Number::make(ARBITRARY_VALUE);
    auto          blocking_number = Number::make(4 * ARBITRARY_VALUE);
    board.at(2, 3).place(moving_number);
    board.at(2, 0).place(blocking_number);

    board.slide(Direction::left);

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

    board.slide(Direction::left);

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

    board.slide(Direction::left);

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
    auto          moving_num_ptr        = moving_number.get();
    auto          moving_merging_number = Number::make(ARBITRARY_VALUE);
    auto          blocked_number        = Number::make(ARBITRARY_VALUE);
    board.at(2, 2).place(moving_number);
    board.at(2, 1).place(moving_merging_number);
    board.at(2, 0).place(blocked_number);

    board.slide(Direction::left);

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

    board.slide(Direction::left);

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

    board.slide(Direction::left);

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

    board.slide(Direction::left);

    CHECK_TRUE(board.at(2, 0).hasNumber());
    CHECK_TRUE(board.at(2, 1).hasNumber());
    CHECK_TRUE(board.at(2, 2).hasNumber());
    CHECK_FALSE(board.at(2, 3).hasNumber());
    CHECK_EQUAL(ARBITRARY_VALUE, board.at(2, 0).number()->value());
    CHECK_EQUAL(4 * ARBITRARY_VALUE, board.at(2, 1).number()->value());
    CHECK_EQUAL(4 * ARBITRARY_VALUE, board.at(2, 2).number()->value());
}

TEST(BoardTest, SlideTwiceMergePreviousMergedNumbers)
{
    BoardTestable board;
    auto          num_0 = Number::make(4);
    auto          num_1 = Number::make(2);
    auto          num_2 = Number::make(2);
    board.at(0, 0).place(num_0);
    board.at(0, 1).place(num_1);
    board.at(0, 3).place(num_2);
    board.slide(Direction::left);

    board.slide(Direction::left);

    CHECK_TRUE(board.at(0, 0).hasNumber());
    CHECK_FALSE(board.at(0, 1).hasNumber());
    CHECK_FALSE(board.at(0, 2).hasNumber());
    CHECK_FALSE(board.at(0, 3).hasNumber());
    CHECK_EQUAL(8, board.at(0, 0).number()->value());
}

TEST(BoardTest, PlaceNumberRandomly)
{
    BoardTestable board;
    auto          number = Number::make(ARBITRARY_VALUE);

    board.placeNumberRandomly(number);

    CHECK_EQUAL(1, board.count());
}

TEST(BoardTest, PlaceNumberRandomlyOutOfSpace)
{
    BoardTestable board;
    while(board.count() != board.size())
    {
        auto n = Number::make(ARBITRARY_VALUE);
        board.placeNumberRandomly(n);
    }
    auto number = Number::make(ARBITRARY_VALUE);

    CHECK_THROWS_STDEXCEPT(
        std::runtime_error, "no space left on board",
        board.placeNumberRandomly(number));
}

TEST(BoardTest, GetMaxNumberOfNone)
{
    auto board = Board::make();

    auto max = board->getMaxNumber();

    CHECK_EQUAL(0, max);
}

TEST(BoardTest, GetMaxNumberOfOne)
{
    BoardTestable board;
    auto          number = Number::make(ARBITRARY_VALUE);
    board.at(2, 2).place(number);

    auto max = board.getMaxNumber();

    CHECK_EQUAL(ARBITRARY_VALUE, max);
}

TEST(BoardTest, GetMaxNumberOfAll)
{
    BoardTestable board;
    auto          number = Number::make(1024);
    board.placeNumberRandomly(number);
    while(board.count() != board.size())
    {
        number = Number::make(ARBITRARY_VALUE);
        board.placeNumberRandomly(number);
    }

    auto max = board.getMaxNumber();

    CHECK_EQUAL(1024, max);
}

TEST(BoardTest, HasFreeSpaceWhenEmpty)
{
    BoardTestable board;

    auto has_space = board.hasFreeSpaces();

    CHECK_EQUAL(true, has_space);
}

TEST(BoardTest, HasFreeSpaceWhenAlmostFull)
{
    BoardTestable board;
    while(board.count() < (board.size() - 1))
    {
        auto number = Number::make(ARBITRARY_VALUE);
        board.placeNumberRandomly(number);
    }

    auto has_space = board.hasFreeSpaces();

    CHECK_EQUAL(true, has_space);
}

TEST(BoardTest, HasFreeSpaceWhenFull)
{
    BoardTestable board;
    while(board.count() != board.size())
    {
        auto number = Number::make(ARBITRARY_VALUE);
        board.placeNumberRandomly(number);
    }

    auto has_space = board.hasFreeSpaces();

    CHECK_EQUAL(false, has_space);
}

TEST(BoardTest, CanSlideWhenEmpty)
{
    auto board = Board::make();

    auto can_slide = board->canSlide();

    CHECK_EQUAL(true, can_slide);
}


TEST(BoardTest, CanSlideWhenFullNotMergeable)
{
    BoardTestable board;
    board.fill(
    {
        { 16, 32, 16, 32 },
        { 32, 16, 32, 16 },
        { 16, 32, 16, 32 },
        { 32, 16, 32, 16 }
    });

    auto can_slide = board.canSlide();

    CHECK_EQUAL(false, can_slide);
}

TEST(BoardTest, CanSlideWhenAlmostFullNotMergeable)
{
    BoardTestable board;
    board.fill(
    {
        { 16, 32, 16, 32 },
        { 32, 16, 32, 16 },
        { 16, 32, 16, 32 },
        { 32, 16, 32, 0  }
    });

    auto can_slide = board.canSlide();

    CHECK_EQUAL(true, can_slide);
}
