#include "testutils.hpp"
#include "../2048/domain/number.hpp"

namespace
{
const Number::Value ARBITRARY_VALUE = 8;
}

TEST_GROUP(NumberTest) {};

TEST(NumberTest, Creation)
{
    Number number(ARBITRARY_VALUE);
    CHECK_EQUAL(ARBITRARY_VALUE, number.value());
}

TEST(NumberTest, CreationByMake)
{
    auto number = Number::make(ARBITRARY_VALUE);
    CHECK_TRUE(number);
    CHECK_EQUAL(ARBITRARY_VALUE, number->value());
}

TEST(NumberTest, ThrowsOnCreationWithValueLessThanTwo)
{
    CHECK_THROWS_STDEXCEPT(
        std::runtime_error, "value cannot be less than 2", Number(1));
}

TEST(NumberTest, ThrowsOnCreationWithValue3NotPowerOf2)
{
    CHECK_THROWS_STDEXCEPT(
        std::runtime_error, "value must be power of 2", Number(3));
}

TEST(NumberTest, ThrowsOnCreationWithValue6NotPowerOf2)
{
    CHECK_THROWS_STDEXCEPT(
        std::runtime_error, "value must be power of 2", Number(6));
}

TEST(NumberTest, MergeDoubleValue)
{
    Number number_1(ARBITRARY_VALUE);
    Number::Movable number_2(new Number(ARBITRARY_VALUE));
    number_1.merge(number_2);
    CHECK_EQUAL(2 * ARBITRARY_VALUE, number_1.value());
}

TEST(NumberTest, MergeRemoveNumber)
{
    Number number_1(ARBITRARY_VALUE);
    Number::Movable number_2(new Number(ARBITRARY_VALUE));
    number_1.merge(number_2);
    CHECK_FALSE(number_2);
}

TEST(NumberTest, MergeBadValues)
{
    Number number_1(ARBITRARY_VALUE);
    Number::Movable number_2(new Number(ARBITRARY_VALUE * 2));
    CHECK_THROWS_STDEXCEPT(
        std::runtime_error, "merging numbers must have the same value",
        number_1.merge(number_2));
}
