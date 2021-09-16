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

namespace my
{
	class SHARED_EXPORT printer
	{
	public:
		static void say_something();
	};
}
