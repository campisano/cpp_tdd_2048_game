#include <cstdint>
#include "CppUTest/TestHarness.h"
#include "../2048/domain/board.hpp"

namespace
{
const std::size_t EXPECTED_BOARD_SIZE = 16;
}

TEST_GROUP(BoardTest)
{
    Board * m_board;

    void setup()
    {
        m_board = new Board();
    }
    void teardown()
    {
        delete m_board;
    }
};

TEST(BoardTest, Creation)
{
    CHECK(NULL != m_board);
    CHECK_EQUAL(EXPECTED_BOARD_SIZE, m_board->size());
}
