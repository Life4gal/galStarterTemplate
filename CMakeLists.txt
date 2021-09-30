# Set the minimum version of CMake that can be used
# To find the cmake version run
# $ cmake --version
cmake_minimum_required(VERSION 3.12...3.20)

set(
		GALSTARTERTEMPLATE_MAJOR_VERSION
		0
)

set(
		GALSTARTERTEMPLATE_MINOR_VERSION
		0
)

set(
		GALSTARTERTEMPLATE_PATCH_VERSION
		6
)

set(
		GALSTARTERTEMPLATE_VERSION
		${GALSTARTERTEMPLATE_MAJOR_VERSION}.${GALSTARTERTEMPLATE_MINOR_VERSION}.${GALSTARTERTEMPLATE_PATCH_VERSION}
)

# Set the project name
project (
		galStarterTemplate
		VERSION ${GALSTARTERTEMPLATE_VERSION}
)

set(CMAKE_MODULE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/cmake")

include(${CMAKE_MODULE_PATH}/prepare-3rd-party.cmake)

# enable test
enable_testing()
# Include google test
include(${GOOGLE_TEST_PATH}/google-test.cmake)
# Include CPM
include(${CPM_PATH}/CPM.cmake)

# global set, locally set use no CMAKE_ version
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

add_subdirectory(my_cool_static_part)
add_subdirectory(my_cool_shared_part)
add_subdirectory(my_awesome_application)
