#include <fmt/format.h>
#include <something.hpp>

namespace something {
	void greeter::hello(const std::string& who) {
		fmt::print("Hello {}!\n", who);
	}

	std::string greeter::say(const std::string& word) {
		return fmt::format("{} {} {} {} {}: {}!", "You", "want", "me", "to", "say", word);
	}
}// namespace something