# Set the minimum version of CMake that can be used
# To find the cmake version run
# $ cmake --version
cmake_minimum_required(VERSION 3.12...3.20)

# Set the project name
project (
		hello-cxx-standard
		VERSION 42
		LANGUAGES CXX
)

if(CMAKE_VERSION VERSION_GREATER 3.1)
	set(HAS_CMAKE_CXX_STANDARD TRUE)
else()
	set(HAS_CMAKE_CXX_STANDARD FALSE)
endif(CMAKE_VERSION VERSION_GREATER 3.1)

# try conditional compilation and add flag
include(CheckCXXCompilerFlag)
CHECK_CXX_COMPILER_FLAG("-std=c++20" COMPILER_SUPPORTS_CXX20)
if(COMPILER_SUPPORTS_CXX20)
	if(${HAS_CMAKE_CXX_STANDARD})
		set(CMAKE_CXX_STANDARD 20)
	else()
		set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++20")
	endif(${HAS_CMAKE_CXX_STANDARD})
else()
	CHECK_CXX_COMPILER_FLAG("-std=c++17" COMPILER_SUPPORTS_CXX17)
	if(COMPILER_SUPPORTS_CXX17)
		set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++17")
	else()
		CHECK_CXX_COMPILER_FLAG("-std=c++11" COMPILER_SUPPORTS_CXX11)
		if(COMPILER_SUPPORTS_CXX11)
			set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")
		else()
			message(FATAL_ERROR "The compiler ${CMAKE_CXX_COMPILER} even has no C++11 support. Please use a different C++ compiler.")
		endif(COMPILER_SUPPORTS_CXX11)
	endif(COMPILER_SUPPORTS_CXX17)
endif(COMPILER_SUPPORTS_CXX20)

# Print the list of known compile features for this version of CMake
message("List of compile features: ${CMAKE_CXX_COMPILE_FEATURES}")

# Add an executable
add_executable(${PROJECT_NAME} main.cpp)

# set the C++ standard to the appropriate standard for using auto and constexpr
target_compile_features(
		${PROJECT_NAME}
		PUBLIC
		cxx_auto_type
		cxx_constexpr
)

# Set a default C++ compile flag
set (
		CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -O2 -fpic -Werror"
		CACHE
		STRING "Set C++ Compiler Flags" FORCE
)

# Define a macro
add_compile_definitions(CURRENT_CMAKE_CXX_FLAGS="${CMAKE_CXX_FLAGS}")
