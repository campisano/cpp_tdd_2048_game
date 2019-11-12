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
    Position position;
    position.place(n1);
    CHECK_THROWS_STDEXCEPT(
        std::runtime_error, "position already contain a number",
        position.place(n2));
}

TEST(PositionTest, HasLeft)
{
    Position position;
    Position p_left;
    position.left(p_left);
    CHECK_EQUAL(&p_left, &position.left());
}

TEST(PositionTest, ThrowsOnGetEmptyLeft)
{
    Position position;
    CHECK_THROWS_STDEXCEPT(
        std::runtime_error, "there is no left position", position.left());
}
