# Set the minimum version of CMake that can be used
# To find the cmake version run
# $ cmake --version
cmake_minimum_required(VERSION 3.12...3.20)

# Set the project name
project (
		hello-headers
		VERSION 42
		LANGUAGES CXX
)

# Define a macro
add_compile_definitions(SAY_SOMETHING="my project name is ${PROJECT_NAME}")

# Create a sources variable with a link to all cpp files to compile
set(
		SOURCES
		src/hello.cpp
		src/main.cpp
		)

# Add an executable with the above sources
add_executable(
		${PROJECT_NAME}
		${SOURCES}
)

# Set the directories that should be included in the build command for this target
# when running g++ these will be included as -I/directory/path/
target_include_directories(
		${PROJECT_NAME}
		PRIVATE
		${PROJECT_SOURCE_DIR}/include
		)
