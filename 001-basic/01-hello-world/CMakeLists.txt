# Set the minimum version of CMake that can be used
# To find the cmake version run
# $ cmake --version
cmake_minimum_required(VERSION 3.12...3.20)

# Set the project name
project (
		hello-world
		VERSION 42
		LANGUAGES CXX
)

# Define a macro
add_compile_definitions(CURRENT_CMAKE_VERSION="${CMAKE_VERSION}")

# Add an executable
add_executable(${PROJECT_NAME} main.cpp)
