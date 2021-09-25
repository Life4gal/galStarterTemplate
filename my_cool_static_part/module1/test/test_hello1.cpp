#include <gtest/gtest.h>

#include <module1/hello1.hpp>

using namespace my;

TEST(TestStaticModule1, TestHello1)
{
	ASSERT_STREQ(printer1::say_something().c_str(), "Hello static module1!");
}
