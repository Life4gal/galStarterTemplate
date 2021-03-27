#include <gtest/gtest.h>

#include <cxxopts.hpp>
#include <something.hpp>

int main(int argc, char **argv) {
	cxxopts::Options options("galStarterTemplateExec", "A Exec for galStarterTemplate.");

	auto adder = options.add_options("CLI args");
	adder("h,hello", "Say hello, give your name", cxxopts::value<std::string>()->default_value("World"));
	adder("s,say", "Say something, give a word", cxxopts::value<std::string>()->default_value("World"));
	adder("j,json", "Receive a json", cxxopts::value<bool>()->default_value("false"));
	adder("d,debug", "Run google-test", cxxopts::value<bool>()->default_value("false"));
	adder("u,usage", "Print usage");

	try {
		auto result = options.parse(argc, argv);

		if (result.count("usage") || result.arguments().empty()) {
			std::cout << options.help() << std::endl;
			return 0;
		} else if (result["debug"].as<bool>()) {
			testing::InitGoogleTest(&argc, argv);
			return RUN_ALL_TESTS();
		} else if (result.count("hello")) {
			auto who = result["hello"].as<std::string>();
			something::greeter::hello(who);
		} else if (result.count("say")) {
			auto word = result["say"].as<std::string>();
			std::cout << something::greeter::say(word) << std::endl;
		} else if (result.count("json")) {
			std::cout << something::greeter::hello_json() << std::endl;
		}
	} catch (cxxopts::missing_argument_exception &what) {
		std::cout << "Missing argument: " << what.what() << '\n'
				  << options.help() << std::endl;
		return -1;
	} catch (cxxopts::OptionParseException &what) {
		std::cout << "Invalid argument: " << what.what() << '\n'
				  << options.help() << std::endl;
		return -1;
	} catch (std::bad_cast &what) {
		std::cout << "Bad argument format: " << what.what() << '\n'
				  << options.help() << std::endl;
		return -1;
	} catch (...) {
		std::cout << "Unknown Error!" << '\n'
				  << options.help() << std::endl;
		return -1;
	}

	return 0;
}
