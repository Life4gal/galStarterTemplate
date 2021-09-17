# Set the minimum version of CMake that can be used
# To find the cmake version run
# $ cmake --version
cmake_minimum_required(VERSION 3.12...3.20)

# Set the project name
project (
		hello-build-type
		VERSION 42
		LANGUAGES CXX
)

# Set a default build type if none was specified
if(NOT CMAKE_BUILD_TYPE AND NOT CMAKE_CONFIGURATION_TYPES)
	message("Setting build type to 'RelWithDebInfo' as none was specified.")
	set(
			CMAKE_BUILD_TYPE RelWithDebInfo
			CACHE STRING "Choose the type of build." FORCE
	)
	# Set the possible values of build type for cmake-gui
	set_property(
			CMAKE_BUILD_TYPE
			PROPERTY CACHE
			STRINGS "Debug" "Release" "MinSizeRel" "RelWithDebInfo"
	)
else()
	message("Current build type is: ${CMAKE_BUILD_TYPE}")
endif(NOT CMAKE_BUILD_TYPE AND NOT CMAKE_CONFIGURATION_TYPES)

# Define a macro
add_compile_definitions(CURRENT_CMAKE_BUILD_TYPE="${CMAKE_BUILD_TYPE}")

# Add an executable
add_executable(${PROJECT_NAME} main.cpp)
