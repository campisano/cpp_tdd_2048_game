#include "CppUTest/TestHarness.h"
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
