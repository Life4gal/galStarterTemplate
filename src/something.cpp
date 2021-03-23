#include <something.hpp>

namespace something
{
	void greeter::hello()
	{
		std::cout << "Hello World!" << std::endl;
	}

	std::string greeter::say()
	{
		return {"Hello World!"};
	}
}