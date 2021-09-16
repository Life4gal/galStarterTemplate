# Set the minimum version of CMake that can be used
# To find the cmake version run
# $ cmake --version
cmake_minimum_required(VERSION 3.12...3.20)

# Set the project name
project (
		hello-static-library
		VERSION 42
		LANGUAGES CXX
)

# LIBRARY NAME
set(
		LIBRARY_NAME
		${PROJECT_NAME}_library
)

# BINARY NAME
set(
		BINARY_NAME
		${PROJECT_NAME}_binary
)

# Define a macro
add_compile_definitions(SAY_SOMETHING="my project name is ${PROJECT_NAME}, my library name is ${LIBRARY_NAME} and my binary name is ${BINARY_NAME}")

############################################################
# Create a library
############################################################

# Generate the static library from the library sources
add_library(
		${LIBRARY_NAME}
		STATIC
		src/hello.cpp
)

target_include_directories(
		${LIBRARY_NAME}
		PUBLIC
		${PROJECT_SOURCE_DIR}/include
)

############################################################
# Create an executable
############################################################

# Add an executable with the above sources
add_executable(
		${BINARY_NAME}
		src/main.cpp
		)

# link the new ${LIBRARY_NAME} target with the ${BINARY_NAME} target
target_link_libraries(
		${BINARY_NAME}
		PRIVATE
		${LIBRARY_NAME}
		)
