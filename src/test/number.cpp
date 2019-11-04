#include "testutils.hpp"
#include "../2048/domain/number.hpp"

namespace
{
const uint32_t ARBITRARY_VALUE = 8;
}

TEST_GROUP(NumberTest)
{
    Number * m_number;

    void setup()
    {
        m_number = new Number(ARBITRARY_VALUE);
    }
    void teardown()
    {
        delete m_number;
    }
};

TEST(NumberTest, Creation)
{
    CHECK(NULL != m_number);
    CHECK_EQUAL(ARBITRARY_VALUE, m_number->value());
}

TEST(NumberTest, CreationWithValueLessThanTwo)
{
    CHECK_THROWS_STDEXCEPT(
        std::runtime_error, Number(1), "value cannot be less than 2");
}

TEST(NumberTest, CreationWithValue3NotPowerOf2)
{
    CHECK_THROWS_STDEXCEPT(
        std::runtime_error, Number(3), "value must be power of 2");
}

TEST(NumberTest, CreationWithValue6NotPowerOf2)
{
    CHECK_THROWS_STDEXCEPT(
        std::runtime_error, Number(6), "value must be power of 2");
}
