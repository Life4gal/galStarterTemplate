#include <iostream>
#include <shared/hello.hpp>

namespace my
{
	void shared_printer::say_something() {
		std::cout << "You just want to say: " SAY_SHARED_LIBRARY << std::endl;
	}
}
