# Set the minimum version of CMake that can be used
# To find the cmake version run
# $ cmake --version
cmake_minimum_required(VERSION 3.12...3.20)

# Set the project name
project (
		hello-compile-flag
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

target_compile_definitions(
		${PROJECT_NAME}
		PRIVATE
		A_FLAG="BALABALA"
)

# Define a macro
add_compile_definitions(CURRENT_CMAKE_CXX_FLAGS="${CMAKE_CXX_FLAGS}")
