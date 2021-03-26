#ifndef STARTER_TEMPLATE_SOMETHING_HPP
#define STARTER_TEMPLATE_SOMETHING_HPP

#include <iostream>
#include <string>

namespace something {
	class greeter {
	public:
		static void hello(const std::string& who);

		[[nodiscard]] static std::string say(const std::string& word);

		[[nodiscard]] static std::string hello_json();
	};
}// namespace something

#endif
