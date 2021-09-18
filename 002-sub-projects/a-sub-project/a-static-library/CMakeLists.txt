# Set the project name
project (
		hello-static-library
		VERSION 42
		LANGUAGES CXX
)

# Define a macro
add_compile_definitions(SAY_STATIC_LIBRARY="my static library name is ${PROJECT_NAME}")

############################################################
# Create a library
############################################################

# Generate the static library from the library sources
add_library(
		${PROJECT_NAME}
		STATIC
		src/hello.cpp
)

add_library(
		A_STATIC_LIBRARY::HELLO
		ALIAS
		${PROJECT_NAME}
)

target_include_directories(
		${PROJECT_NAME}
		PUBLIC
		${PROJECT_SOURCE_DIR}/include
)
