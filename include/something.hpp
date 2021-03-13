#ifndef STARTER_TEMPLATE_SOMETHING_HPP
#define STARTER_TEMPLATE_SOMETHING_HPP

#include <iostream>
#include <string>

namespace something
{
	void hello()
	{
		std::cout << "Hello World!" << std::endl;
	}

	std::string say()
	{
		return {"Hello World!"};
	}
}

#endif
