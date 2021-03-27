#include <fmt/format.h>
#include <nlohmann/json.hpp>
#include <something.hpp>

namespace something {
	void greeter::hello(const std::string& who) {
		fmt::print("Hello {}!\n", who);
	}

	std::string greeter::say(const std::string& word) {
		return fmt::format("{} {} {} {} {}: {}!", "You", "want", "me", "to", "say", word);
	}

	std::string greeter::hello_json() {
		nlohmann::json json;

		json["hello"] = "Hello ";
		json["world"] = "Json!";

		return json.dump();
	}
}// namespace something