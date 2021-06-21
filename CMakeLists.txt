cmake_minimum_required(VERSION 3.13...3.20)

# set your project name
project(
		galStarterTemplate
		VERSION 2.0.0
		LANGUAGES CXX
)

set(CMAKE_MODULE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/cmake")

add_subdirectory(sub-project1)
add_subdirectory(sub-project2)
add_subdirectory(sub-project3)
