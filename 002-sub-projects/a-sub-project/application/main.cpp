#include <iostream>

#include <headonly/hello.hpp>
#include <shared/hello.hpp>
#include <static/hello.hpp>

int main()
{
	std::cout << "Using cmake now! version: " CURRENT_CMAKE_VERSION << std::endl;

	std::cout << "Using interface: " INTERFACE_COME_FROM << std::endl;
	my::interface_printer::say_something();

	std::cout << "Using shared library: " SHARED_LIBRARY_COME_FROM << std::endl;
	my::shared_printer::say_something();

	std::cout << "Using static library: " STATIC_LIBRARY_COME_FROM << std::endl;
	my::static_printer::say_something();
}
