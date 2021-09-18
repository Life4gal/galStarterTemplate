# Set the project name
project (
		hello-world
		VERSION 42
		LANGUAGES CXX
)

# Define a macro
add_compile_definitions(CURRENT_CMAKE_VERSION="${CMAKE_VERSION}")

# cannot use alias
add_compile_definitions(INTERFACE_COME_FROM="${hello-interface_SOURCE_DIR}")
add_compile_definitions(SHARED_LIBRARY_COME_FROM="${hello-shared-library_SOURCE_DIR}")
add_compile_definitions(STATIC_LIBRARY_COME_FROM="${hello-static-library_SOURCE_DIR}")

# Add an executable
add_executable(${PROJECT_NAME} main.cpp)

target_link_libraries(
		${PROJECT_NAME}
		PRIVATE
		A_INTERFACE::HELLO
		A_SHARED_LIBRARY::HELLO
		A_STATIC_LIBRARY::HELLO
)
