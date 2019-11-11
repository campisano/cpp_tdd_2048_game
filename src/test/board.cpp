#include <cstdint>
#include "CppUTest/TestHarness.h"
#include "../2048/domain/board.hpp"

namespace
{
const std::size_t EXPECTED_BOARD_SIZE = 16;
}

TEST_GROUP(BoardTest) {};

TEST(BoardTest, Creation)
{
    Board board;
    CHECK_EQUAL(EXPECTED_BOARD_SIZE, board.size());
}
