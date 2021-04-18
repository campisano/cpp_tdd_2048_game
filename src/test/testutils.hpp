#ifndef TESTUTILS__HPP__
#define TESTUTILS__HPP__

#include <doctest.h>

#define TEST_GROUP_BEGIN(group_name) TEST_SUITE_BEGIN(#group_name)
#define TEST_GROUP_END() TEST_SUITE_END()
#define TEST(name) TEST_CASE(#name)

#define CHECK_EQUAL(a, b) CHECK_EQ(a, b)
#define CHECK_TRUE(a) CHECK_EQ(true, a)
#define CHECK_THROWS_STDEXCEPT(type, message, action) CHECK_THROWS_WITH_AS(action, message, type)

#endif
