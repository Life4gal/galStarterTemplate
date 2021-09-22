# Set the minimum version of CMake that can be used
# To find the cmake version run
# $ cmake --version
cmake_minimum_required(VERSION 3.12...3.20)

# Set the project name
project (
		hello-use-cpm
		VERSION 42
		LANGUAGES CXX
)

# Add an executable
add_executable(${PROJECT_NAME} main.cpp)

set(CMAKE_MODULE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/cmake")

include(${CMAKE_MODULE_PATH}/CPM.cmake)

# Add fmt support
CPMAddPackage(
		NAME fmt
		GIT_TAG master
		GITHUB_REPOSITORY fmtlib/fmt
		# create an installable target, this is necessary
		# https://github.com/fmtlib/fmt/blob/9cb347b4b2e80fc9fbf57b8621746663c3f870f6/CMakeLists.txt#L67
		OPTIONS
		"FMT_INSTALL ON"
		"FMT_TEST OFF"
)

target_link_libraries(
		${PROJECT_NAME}
		PRIVATE
		fmt
)
