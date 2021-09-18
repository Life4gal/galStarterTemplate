cmake_minimum_required(VERSION 3.12...3.20)

# Set the project name
project(hello-configure-files)

# set a project version
set(${PROJECT_NAME}_VERSION_MAJOR 1)
set(${PROJECT_NAME}_VERSION_MINOR 2)
set(${PROJECT_NAME}_VERSION_PATCH 3)
set(${PROJECT_NAME}_VERSION "${${PROJECT_NAME}_VERSION_MAJOR}.${${PROJECT_NAME}_VERSION_MINOR}.${${PROJECT_NAME}_VERSION_PATCH}")

# Call configure files on version.hpp.in to set the version.
# Uses the standard ${VARIABLE} syntax in the file
configure_file(version.hpp.in ${PROJECT_BINARY_DIR}/version.hpp)

# configure the path.hpp.in file.
# This file can only use the @VARIABLE@ syntax in the file
configure_file(path.hpp.in ${PROJECT_BINARY_DIR}/path.hpp @ONLY)

# Add an executable
add_executable(
		${PROJECT_NAME}
		main.cpp
)

# include the directory with the new files
target_include_directories(
		${PROJECT_NAME}
		PUBLIC
		${CMAKE_BINARY_DIR}
)
