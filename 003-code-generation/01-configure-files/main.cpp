#include <iostream>

#include "version.hpp"
#include <path.hpp>

int main()
{
	std::cout << "project path: " << my::project_path << "\nproject version: " << my::project_version << std::endl;
}
