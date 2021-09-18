#include <iostream>
#include <static/hello.hpp>

namespace my
{
	void static_printer::say_something() {
		std::cout << "You just want to say: " SAY_STATIC_LIBRARY << std::endl;
	}
}
