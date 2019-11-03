#include "CppUTest/TestHarness.h"
#include <array>
#include <cstdint>

namespace
{
const uint8_t BOARD_SIZE = 16;
using Board = std::array<void *, BOARD_SIZE>;
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
    CHECK_EQUAL(BOARD_SIZE, m_board->size());
}
