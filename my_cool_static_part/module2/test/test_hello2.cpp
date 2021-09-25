#include <gtest/gtest.h>

#include <module2/hello2.hpp>

using namespace my;

TEST(TestStaticModule2, TestHello2)
{
	ASSERT_STREQ(printer2::say_something().c_str(), "Hello static module2!");
}
