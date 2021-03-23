#include <gtest/gtest.h>

#include <cxxopts.hpp>

int main(int argc, char** argv) {
	cxxopts::Options options("galStarterTemplateTest", "A test for galStarterTemplate.");

	options.add_options("CLI args")("b,bar", "Param bar", cxxopts::value<std::string>()->default_value("bar"))("d,debug", "Run google-test", cxxopts::value<bool>()->default_value("false"))("f,foo", "Param foo", cxxopts::value<int>()->default_value("10"))("h,help", "Print usage");

	auto result = options.parse(argc, argv);

	if (result.count("help")) {
		std::cout << options.help() << std::endl;
		return 0;
	}

	auto debug = result["debug"].as<bool>();

	if (debug) {
		testing::InitGoogleTest(&argc, argv);
		return RUN_ALL_TESTS();
	}

	auto bar = result["bar"].as<std::string>();
	auto foo = result["foo"].as<int>();

	std::cout << "Curr:"
			  << " [bar]->" << bar << " [foo]->" << foo << std::endl;

	return 0;
}
