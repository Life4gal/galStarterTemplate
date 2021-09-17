#include <iostream>

#include <boost/filesystem.hpp>

int main()
{
	namespace fs = boost::filesystem;

	std::cout << "searching path: " << fs::current_path() << '\n';
	for(auto it = fs::directory_iterator{fs::current_path()}; it != fs::directory_iterator{}; ++it)
	{
		std::cout << "\tfound file: " << it->path().filename() << '\n';
	}

	std::cout << "searching module path: " << CURRENT_CMAKE_MODULE_PATH "\n";
	for(auto it = fs::directory_iterator{CURRENT_CMAKE_MODULE_PATH}; it != fs::directory_iterator{}; ++it)
	{
		std::cout << "\tfound module: " << it->path().filename() << '\n';
	}
}
