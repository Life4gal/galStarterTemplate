#include <hello.hpp>
#include <iostream>

namespace my
{
	void printer::say_something() {
		std::cout << "You just want to say: " SAY_SOMETHING << std::endl;
	}
}
