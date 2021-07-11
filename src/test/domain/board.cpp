#include "../testutils.hpp"

#include "doubles/board_testable.hpp"
#include <stdexcept>

namespace
{
const Board::Size   EXPECTED_BOARD_SIZE = 16;
const Number::Value ARBITRARY_VALUE     = 8;
}

TEST_GROUP_BEGIN(BoardTest);

TEST(Creation)
{
    BoardTestable board(4, 4);

    CHECK_EQUAL(EXPECTED_BOARD_SIZE, board.size());
    CHECK_EQUAL(0, board.count());
}

TEST(AtInside)
{
    BoardTestable board(4, 4);

    board.at(0, 0);
    board.at(3, 3);
}

TEST(ThrowsOnAtUpOutside)
{
    BoardTestable board(4, 4);

    CHECK_THROWS_STDEXCEPT(
        std::out_of_range, "out of board boundaries", board.at(-1, 0));
}

TEST(ThrowsOnAtDownOutside)
{
    BoardTestable board(4, 4);

    CHECK_THROWS_STDEXCEPT(
        std::out_of_range, "out of board boundaries", board.at(4, 0));
}

TEST(ThrowsOnAtLeftOutside)
{
    BoardTestable board(4, 4);

    CHECK_THROWS_STDEXCEPT(
        std::out_of_range, "out of board boundaries", board.at(0, -1));
}

TEST(ThrowsOnAtRightOutside)
{
    BoardTestable board(4, 4);

    CHECK_THROWS_STDEXCEPT(
        std::out_of_range, "out of board boundaries", board.at(0, 4));
}

TEST(AtEdgeUpLeft)
{
    BoardTestable board(4, 4);

    CHECK_FALSE(board.at(0, 0).hasUp());
    CHECK_TRUE(board.at(0, 0).hasDown());
    CHECK_FALSE(board.at(0, 0).hasLeft());
    CHECK_TRUE(board.at(0, 0).hasRight());
}

TEST(AtEdgeUpRight)
{
    BoardTestable board(4, 4);

    CHECK_FALSE(board.at(0, 3).hasUp());
    CHECK_TRUE(board.at(0, 3).hasDown());
    CHECK_TRUE(board.at(0, 3).hasLeft());
    CHECK_FALSE(board.at(0, 3).hasRight());
}

TEST(AtEdgeDownLeft)
{
    BoardTestable board(4, 4);

    CHECK_TRUE(board.at(3, 0).hasUp());
    CHECK_FALSE(board.at(3, 0).hasDown());
    CHECK_FALSE(board.at(3, 0).hasLeft());
    CHECK_TRUE(board.at(3, 0).hasRight());
}

TEST(AtEdgeDownRight)
{
    BoardTestable board(4, 4);

    CHECK_TRUE(board.at(3, 3).hasUp());
    CHECK_FALSE(board.at(3, 3).hasDown());
    CHECK_TRUE(board.at(3, 3).hasLeft());
    CHECK_FALSE(board.at(3, 3).hasRight());
}

TEST(SlideLeft)
{
    BoardTestable board(4, 4);
    auto          number  = Number::make(ARBITRARY_VALUE);
    auto          num_ptr = number.get();
    board.at(2, 2).place(number);

    board.slide(Direction::left);

    CHECK_FALSE(board.at(2, 2).hasNumber());
    CHECK_TRUE(board.at(2, 0).hasNumber());
    CHECK_EQUAL(num_ptr, board.at(2, 0).number().get());
}

TEST(SlideRight)
{
    BoardTestable board(4, 4);
    auto          number  = Number::make(ARBITRARY_VALUE);
    auto          num_ptr = number.get();
    board.at(1, 1).place(number);

    board.slide(Direction::right);

    CHECK_FALSE(board.at(1, 1).hasNumber());
    CHECK_TRUE(board.at(1, 3).hasNumber());
    CHECK_EQUAL(num_ptr, board.at(1, 3).number().get());
}

TEST(SlideUp)
{
    BoardTestable board(4, 4);
    auto          number  = Number::make(ARBITRARY_VALUE);
    auto          num_ptr = number.get();
    board.at(2, 2).place(number);

    board.slide(Direction::up);

    CHECK_FALSE(board.at(2, 2).hasNumber());
    CHECK_TRUE(board.at(0, 2).hasNumber());
    CHECK_EQUAL(num_ptr, board.at(0, 2).number().get());
}

TEST(SlideDown)
{
    BoardTestable board(4, 4);
    auto          number  = Number::make(ARBITRARY_VALUE);
    auto          num_ptr = number.get();
    board.at(1, 1).place(number);

    board.slide(Direction::down);

    CHECK_FALSE(board.at(1, 1).hasNumber());
    CHECK_TRUE(board.at(3, 1).hasNumber());
    CHECK_EQUAL(num_ptr, board.at(3, 1).number().get());
}

TEST(SlideIsAppliedToAllNumbers)
{
    BoardTestable board(4, 4);
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

TEST(SlideNotOverBoardEdge)
{
    BoardTestable board(4, 4);
    auto          number = Number::make(ARBITRARY_VALUE);
    board.at(2, 0).place(number);

    board.slide(Direction::left);

    CHECK_TRUE(board.at(2, 0).hasNumber());
}

TEST(SlideStopOnNotMergeableNumber)
{
    BoardTestable board(4, 4);
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

TEST(SlideStopOnNotMergeableNumberAfterItsMove)
{
    BoardTestable board(4, 4);
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

TEST(SlideMoveAndMergeAtEdgeTwoMergeableNumbers)
{
    BoardTestable board(4, 4);
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

TEST(SlideNotMergeThirdMergeableNumber)
{
    BoardTestable board(4, 4);
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

TEST(SlideMergeTwoByTwoOfFourEqualNumbers)
{
    BoardTestable board(4, 4);
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

TEST(SlideMergeCouplesOfMergeableNumbers)
{
    BoardTestable board(4, 4);
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

TEST(SlideMergeMiddleNumbers)
{
    BoardTestable board(4, 4);
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

TEST(SlideTwiceMergePreviousMergedNumbers)
{
    BoardTestable board(4, 4);
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

TEST(PlaceNumberRandomly)
{
    BoardTestable board(4, 4);
    auto          number = Number::make(ARBITRARY_VALUE);

    board.placeNumberRandomly(number);

    CHECK_EQUAL(1, board.count());
}

TEST(PlaceNumberRandomlyOutOfSpace)
{
    BoardTestable board(4, 4);
    while(board.count() != board.size())
    {
        auto n = Number::make(ARBITRARY_VALUE);
        board.placeNumberRandomly(n);
    }
    auto number = Number::make(ARBITRARY_VALUE);

    CHECK_THROWS_STDEXCEPT(
        std::out_of_range, "no space left on board",
        board.placeNumberRandomly(number));
}

TEST(GetMaxNumberOfNone)
{
    auto board = Board::make(4, 4);

    auto max = board->getMaxNumber();

    CHECK_EQUAL(0, max);
}

TEST(GetMaxNumberOfOne)
{
    BoardTestable board(4, 4);
    auto          number = Number::make(ARBITRARY_VALUE);
    board.at(2, 2).place(number);

    auto max = board.getMaxNumber();

    CHECK_EQUAL(ARBITRARY_VALUE, max);
}

TEST(GetMaxNumberOfAll)
{
    BoardTestable board(4, 4);
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

TEST(HasFreeSpaceWhenEmpty)
{
    BoardTestable board(4, 4);

    auto has_space = board.hasFreeSpaces();

    CHECK_EQUAL(true, has_space);
}

TEST(HasFreeSpaceWhenAlmostFull)
{
    BoardTestable board(4, 4);
    while(board.count() < (board.size() - 1))
    {
        auto number = Number::make(ARBITRARY_VALUE);
        board.placeNumberRandomly(number);
    }

    auto has_space = board.hasFreeSpaces();

    CHECK_EQUAL(true, has_space);
}

TEST(HasFreeSpaceWhenFull)
{
    BoardTestable board(4, 4);
    while(board.count() != board.size())
    {
        auto number = Number::make(ARBITRARY_VALUE);
        board.placeNumberRandomly(number);
    }

    auto has_space = board.hasFreeSpaces();

    CHECK_EQUAL(false, has_space);
}

TEST(CanSlideWhenEmpty)
{
    auto board = Board::make(4, 4);

    auto can_slide = board->canSlide();

    CHECK_EQUAL(true, can_slide);
}


TEST(CanSlideWhenFullNotMergeable)
{
    BoardTestable board(4, 4);
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

TEST(CanSlideWhenAlmostFullNotMergeable)
{
    BoardTestable board(4, 4);
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

TEST_GROUP_END();
