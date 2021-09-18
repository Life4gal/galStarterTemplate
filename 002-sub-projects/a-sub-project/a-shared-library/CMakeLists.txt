# Set the project name
project (
		hello-shared-library
		VERSION 42
		LANGUAGES CXX
)

# Define a macro
add_compile_definitions(SAY_SHARED_LIBRARY="my shared library name is ${PROJECT_NAME}")

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
		${PROJECT_NAME}
		SHARED
		src/hello.cpp
)

add_library(
		A_SHARED_LIBRARY::HELLO
		ALIAS
		${PROJECT_NAME}
)

target_include_directories(
		${PROJECT_NAME}
		PUBLIC
		${PROJECT_SOURCE_DIR}/include
)
