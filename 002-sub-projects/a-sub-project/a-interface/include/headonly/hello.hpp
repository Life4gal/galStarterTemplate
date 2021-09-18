#pragma once

#include <iostream>

namespace my
{
	class interface_printer
	{
	public:
		static void say_something()
		{
			std::cout << "Hello Interface!" << std::endl;
		}
	};
}
