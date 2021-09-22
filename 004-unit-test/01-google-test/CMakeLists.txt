# Set the minimum version of CMake that can be used
# To find the cmake version run
# $ cmake --version
cmake_minimum_required(VERSION 3.12...3.20)

# Set the project name
project (
		hello-googletest
		VERSION 42
		LANGUAGES CXX
)

include(cmake/prepare-3rd-party.cmake)

# Include google test
include(${GOOGLE_TEST_PATH}/google-test.cmake)

set(
		TEST_SOURCE
		test/test1.cpp
)

# Add an executable
add_executable(
		${PROJECT_NAME}
		${TEST_SOURCE}
		main.cpp
)

target_link_libraries(
		${PROJECT_NAME}
		PRIVATE
		gtest_main
)

