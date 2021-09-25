#include <gtest/gtest.h>

#include <module1/hey1.hpp>

using namespace my;

TEST(TestStaticModule1, TestHey1)
{
	ASSERT_STREQ(greeting1::say_something().c_str(), "Hey shared module1!");
}
