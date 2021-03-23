#ifndef STARTER_TEMPLATE_SOMETHING_HPP
#define STARTER_TEMPLATE_SOMETHING_HPP

#include <iostream>
#include <string>

namespace something
{
	class greeter
	{
	public:
		static void hello();

		[[nodiscard]] static std::string say();
	};
}

#endif
