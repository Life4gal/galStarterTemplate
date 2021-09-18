# Set the project name
project (
		hello-interface
		VERSION 42
		LANGUAGES CXX
)

add_library(${PROJECT_NAME} INTERFACE)

add_library(
		A_INTERFACE::HELLO
		ALIAS
		${PROJECT_NAME}
)

target_include_directories(
		${PROJECT_NAME}
		INTERFACE
		${PROJECT_SOURCE_DIR}/include
)
