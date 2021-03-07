#include <gtest/gtest.h>

#include <gal_format_core.hpp>

int main(int argc, char** argv)
{
	testing::InitGoogleTest(&argc, argv);

	gal::format::hello();

	return RUN_ALL_TESTS();
}
