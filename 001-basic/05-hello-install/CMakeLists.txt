# Set the minimum version of CMake that can be used
# To find the cmake version run
# $ cmake --version
cmake_minimum_required(VERSION 3.12...3.20)

# Set the project name
project (
		hello-install
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

# WIN32 dll need export
# see also: http://gernotklingler.com/blog/creating-using-shared-libraries-different-compilers-different-operating-systems/
# see also: https://stackoverflow.com/questions/33062728/cmake-link-shared-library-on-windows/33297026
if(MSVC)
	add_compile_definitions(SHARED_NEED_EXPORT)
endif(MSVC)

############################################################
# Create a library
############################################################

# Generate the shared library from the library sources
add_library(
		${LIBRARY_NAME}
		SHARED
		src/hello.cpp
)

add_library(
		MY::LIBRARY_ALIAS
		ALIAS
		${LIBRARY_NAME}
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
		MY::LIBRARY_ALIAS
)

############################################################
# Install
############################################################

# Binaries
install(
		TARGETS ${BINARY_NAME}
		DESTINATION "install binary target"
)

# Library
install(
		TARGETS ${LIBRARY_NAME}
		LIBRARY
		DESTINATION "install library target"
)

# Header files
install(
		DIRECTORY ${PROJECT_SOURCE_DIR}/include/
		DESTINATION "include file path"
)

# Config
install(
		FILES cmake-hello-install.conf
		DESTINATION "install config"
)
