#pragma once

#ifdef _WIN32
#ifdef SHARED_NEED_EXPORT
#define SHARED_EXPORT __declspec(dllexport)
#else
#define SHARED_EXPORT __declspec(dllimport)
#endif
#else
#define SHARED_EXPORT
#endif

#include <string>

namespace my
{
	class SHARED_EXPORT greeting1
	{
	public:
		static std::string say_something();
	};
}
