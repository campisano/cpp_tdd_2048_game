#include "testutils.hpp"
#include "../2048/domain/number.hpp"

namespace
{
const uint32_t ARBITRARY_VALUE = 8;
const Position ARBITRARY_POSITION;
}

TEST_GROUP(NumberTest) {};

TEST(NumberTest, Creation)
{
    Number number(ARBITRARY_VALUE, ARBITRARY_POSITION);
    CHECK_EQUAL(ARBITRARY_VALUE, number.value());
    CHECK_EQUAL(&ARBITRARY_POSITION, &number.position());
}

TEST(NumberTest, CreationWithValueLessThanTwo)
{
    CHECK_THROWS_STDEXCEPT(
        std::runtime_error, "value cannot be less than 2",
        Number(1, ARBITRARY_POSITION));
}

TEST(NumberTest, CreationWithValue3NotPowerOf2)
{
    CHECK_THROWS_STDEXCEPT(
        std::runtime_error, "value must be power of 2",
        Number(3, ARBITRARY_POSITION));
}

TEST(NumberTest, CreationWithValue6NotPowerOf2)
{
    CHECK_THROWS_STDEXCEPT(
        std::runtime_error, "value must be power of 2",
        Number(6, ARBITRARY_POSITION));
}
