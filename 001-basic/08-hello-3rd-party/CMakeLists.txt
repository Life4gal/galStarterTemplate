# Set the minimum version of CMake that can be used
# To find the cmake version run
# $ cmake --version
cmake_minimum_required(VERSION 3.12...3.20)

# Set the project name
project (
		hello-3rd-party
		VERSION 42
		LANGUAGES CXX
)

# Set a default C++ compile flag
set (
		CMAKE_CXX_FLAGS "-std=c++11 -O2 -fpic -Werror"
		CACHE
		STRING "Set C++ Compiler Flags" FORCE
)

# Add an executable
add_executable(${PROJECT_NAME} main.cpp)

set(Boost_USE_STATIC_LIBS ON)

find_package(
		Boost 1.7 COMPONENTS
		system
		filesystem
		REQUIRED
)

# check if boost was found
if(Boost_FOUND)
	message("Boost found, version: ${Boost_VERSION}")
else()
	message(FATAL_ERROR "Cannot find Boost")
endif(Boost_FOUND)

target_link_libraries(
		${PROJECT_NAME}
		PRIVATE
		Boost::filesystem
)

set(
		CMAKE_CURRENT_VERSION_FOLDER
		${CMAKE_MAJOR_VERSION}.${CMAKE_MINOR_VERSION}
)

# Define a macro
if(MSVC)
	add_compile_definitions(CURRENT_CMAKE_MODULE_PATH="C:\\Program Files\\CMake\\share\\cmake-${CMAKE_CURRENT_VERSION_FOLDER}\\Modules")
else()
	add_compile_definitions(CURRENT_CMAKE_MODULE_PATH="/usr/share/cmake-${CMAKE_CURRENT_VERSION_FOLDER}/Modules")
endif(MSVC)
