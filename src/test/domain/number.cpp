#include "../testutils.hpp"

#include "../../2048/domain/number.hpp"
#include "doubles/number_testable.hpp"

namespace
{
const Number::Value ARBITRARY_VALUE = 8;
}

TEST_GROUP_BEGIN(NumberTest);

TEST(Creation)
{
    auto number = Number::make(ARBITRARY_VALUE);

    CHECK_EQUAL(ARBITRARY_VALUE, number->value());
}

TEST(CreationByMake)
{
    auto number = Number::make(ARBITRARY_VALUE);

    CHECK_TRUE(number != nullptr);
    CHECK_EQUAL(ARBITRARY_VALUE, number->value());
}

TEST(ThrowsOnCreationWithValueNegative)
{
    CHECK_THROWS_STDEXCEPT(
        std::runtime_error, "value cannot be less than 2", Number::make(-1));
}

TEST(ThrowsOnCreationWithValueLessThanTwo)
{
    CHECK_THROWS_STDEXCEPT(
        std::runtime_error, "value cannot be less than 2", Number::make(1));
}

TEST(ThrowsOnCreationWithValue3NotPowerOf2)
{
    CHECK_THROWS_STDEXCEPT(
        std::runtime_error, "value must be power of 2", Number::make(3));
}

TEST(ThrowsOnCreationWithValue6NotPowerOf2)
{
    CHECK_THROWS_STDEXCEPT(
        std::runtime_error, "value must be power of 2", Number::make(6));
}

TEST(MergeDoubleValue)
{
    auto number_1 = Number::make(ARBITRARY_VALUE);
    auto number_2 = Number::make(ARBITRARY_VALUE);

    number_1->merge(number_2);

    CHECK_EQUAL(2 * ARBITRARY_VALUE, number_1->value());
}

TEST(MergeRemoveNumber)
{
    auto number_1 = Number::make(ARBITRARY_VALUE);
    auto number_2 = Number::make(ARBITRARY_VALUE);

    number_1->merge(number_2);

    CHECK_FALSE(number_2);
}

TEST(MergeDeleteNumber)
{
    bool deleted;
    auto number_1 = Number::Movable(new NumberTestable(ARBITRARY_VALUE, deleted));
    auto number_2 = Number::make(ARBITRARY_VALUE);

    number_2->merge(number_1);

    CHECK_TRUE(deleted);
}

TEST(ThrowsOnMergeBadValues)
{
    auto number_1 = Number::make(ARBITRARY_VALUE);
    auto number_2 = Number::make(2 * ARBITRARY_VALUE);

    CHECK_THROWS_STDEXCEPT(
        std::runtime_error,
        "merging numbers must have the same value"
        " and must have not been merged",
        number_1->merge(number_2));
}

TEST(ThrowsOnMergeAlreadyMerged)
{
    auto number_1 = Number::make(ARBITRARY_VALUE);
    auto number_2 = Number::make(ARBITRARY_VALUE);
    auto number_3 = Number::make(2 * ARBITRARY_VALUE);
    number_1->merge(number_2);

    CHECK_THROWS_STDEXCEPT(
        std::runtime_error,
        "merging numbers must have the same value"
        " and must have not been merged",
        number_1->merge(number_3));
}

TEST_GROUP_END();
