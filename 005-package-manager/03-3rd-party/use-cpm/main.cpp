#include <iostream>

#include <fmt/format.h>

int main()
{
	std::cout << fmt::format("hello {}{}{}{}{}{}\n", 'w', 'o', 'r', 'l', 'd', '!');
}
