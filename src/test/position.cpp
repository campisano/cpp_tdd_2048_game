#include "testutils.hpp"
#include "../2048/domain/position.hpp"

namespace
{
const uint32_t ARBITRARY_VALUE = 8;
const Number ARBITRARY_NUMBER(ARBITRARY_VALUE);
}

TEST_GROUP(PositionTest) {};

TEST(PositionTest, Creation)
{
    Position position;
    CHECK_FALSE(position.number());
}
