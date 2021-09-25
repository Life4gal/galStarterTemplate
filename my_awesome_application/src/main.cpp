#include <iostream>

#include <fmt/format.h>

#include <module1/hello1.hpp>
#include <module1/hey1.hpp>
#include <module2/hello2.hpp>

int main()
{
	std::cout << fmt::format(
			"module1::hello1 -> {}\nmodule2::hello2 -> {}\nmodule1::hey -> {}\n",
			my::printer1::say_something(),
			my::printer2::say_something(),
			my::greeting1::say_something()
			);
}
