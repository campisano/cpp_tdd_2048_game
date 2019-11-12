#include "testutils.hpp"
#include "../2048/domain/position.hpp"

namespace
{
const Number::Value ARBITRARY_VALUE = 8;
}

TEST_GROUP(PositionTest) {};

TEST(PositionTest, Creation)
{
    Position position;
    CHECK_FALSE(position.number());
}

TEST(PositionTest, PlacingNumber)
{
    auto number = Number::make(ARBITRARY_VALUE);
    Number * num_ptr = number.get();
    Position position;
    position.place(number);
    CHECK_FALSE(number);
    CHECK_TRUE(position.number());
    CHECK_EQUAL(num_ptr, position.number().get());
}

TEST(PositionTest, ThrowsOnPlacingNumberTwice)
{
    auto n1 = Number::make(ARBITRARY_VALUE);
    auto n2 = Number::make(ARBITRARY_VALUE);
    Position pos;
    pos.place(n1);
    CHECK_THROWS_STDEXCEPT(
        std::runtime_error, "position already contain a number", pos.place(n2));
}

TEST(PositionTest, HasLeft)
{
    Position p;
    Position left;
    p.left(left);
    CHECK_EQUAL(&left, &p.left());
}
