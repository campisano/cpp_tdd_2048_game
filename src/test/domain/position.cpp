#include "../testutils.hpp"

#include "../../2048/domain/position.hpp"

namespace
{
const Number::Value ARBITRARY_VALUE = 8;
}

TEST_GROUP(PositionTest) {};

TEST(PositionTest, Creation)
{
    Position position;

    CHECK_FALSE(position.hasNumber());
    CHECK_FALSE(position.hasLeft());
    CHECK_FALSE(position.hasRight());
    CHECK_FALSE(position.hasUp());
    CHECK_FALSE(position.hasDown());
}

TEST(PositionTest, PlacingNumber)
{
    auto     number  = Number::make(ARBITRARY_VALUE);
    auto     num_ptr = number.get();
    Position position;

    position.place(number);

    CHECK_FALSE(number);
    CHECK_TRUE(position.hasNumber());
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
    Position left;

    position.left(left);

    CHECK_TRUE(position.hasLeft());
    CHECK_EQUAL(&left, &position.left());
}

TEST(PositionTest, ThrowsOnGetEmptyLeft)
{
    Position position;

    CHECK_THROWS_STDEXCEPT(
        std::runtime_error, "there is no left position", position.left());
}

TEST(PositionTest, HasRight)
{
    Position position;
    Position right;

    position.right(right);

    CHECK_TRUE(position.hasRight());
    CHECK_EQUAL(&right, &position.right());
}

TEST(PositionTest, ThrowsOnGetEmptyRight)
{
    Position position;

    CHECK_THROWS_STDEXCEPT(
        std::runtime_error, "there is no right position", position.right());
}

TEST(PositionTest, HasUp)
{
    Position position;
    Position up;

    position.up(up);

    CHECK_TRUE(position.hasUp());
    CHECK_EQUAL(&up, &position.up());
}

TEST(PositionTest, ThrowsOnGetEmptyUp)
{
    Position position;

    CHECK_THROWS_STDEXCEPT(
        std::runtime_error, "there is no up position", position.up());
}

TEST(PositionTest, HasDown)
{
    Position position;
    Position down;

    position.down(down);

    CHECK_TRUE(position.hasDown());
    CHECK_EQUAL(&down, &position.down());
}

TEST(PositionTest, ThrowsOnGetEmptyDown)
{
    Position position;

    CHECK_THROWS_STDEXCEPT(
        std::runtime_error, "there is no down position", position.down());
}

TEST(PositionTest, TransferToEmptyImplyPlaceThere)
{
    auto     number  = Number::make(ARBITRARY_VALUE);
    auto     num_ptr = number.get();
    Position pos_start;
    Position pos_end;
    pos_start.place(number);

    pos_start.transferTo(pos_end);

    CHECK_FALSE(pos_start.hasNumber());
    CHECK_TRUE(pos_end.hasNumber());
    CHECK_EQUAL(num_ptr, pos_end.number().get());
}

TEST(PositionTest, TransferToNotEmptyImplyMergeThere)
{
    auto     num_start = Number::make(ARBITRARY_VALUE);
    auto     num_end   = Number::make(ARBITRARY_VALUE);
    Position pos_start;
    Position pos_end;
    pos_start.place(num_start);
    pos_end.place(num_end);

    pos_start.transferTo(pos_end);

    CHECK_FALSE(pos_start.hasNumber());
    CHECK_TRUE(pos_end.hasNumber());
    CHECK_EQUAL(2 * ARBITRARY_VALUE, pos_end.number()->value());
}
