cmake_minimum_required(VERSION 3.12...3.17)

# set your project name
project(
		galStarterTemplate
		VERSION 0.8.5
		LANGUAGES CXX
)

#####################
# STANDARD PROJECT START
#####################
file(GLOB_RECURSE galStarterTemplateHeader CONFIGURE_DEPENDS "${CMAKE_CURRENT_SOURCE_DIR}/include/*.hpp")
file(GLOB_RECURSE galStarterTemplateSource CONFIGURE_DEPENDS "${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp")

add_library(
		${PROJECT_NAME}
		${galStarterTemplateHeader}
		${galStarterTemplateSource}
)

set_target_properties(
		${PROJECT_NAME} PROPERTIES
		LINKER_LANGUAGE CXX
		CXX_STANDARD 17
)

target_include_directories(
		${PROJECT_NAME}
		PUBLIC
		$<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}/include>
		$<INSTALL_INTERFACE:include/${PROJECT_NAME}-${PROJECT_VERSION}>
)
#####################
# STANDARD PROJECT END
#####################



#####################
# INTERFACE PROJECT START
#####################
#file(GLOB_RECURSE StarterTemplateHeader CONFIGURE_DEPENDS "${CMAKE_CURRENT_SOURCE_DIR}/include")
#file(GLOB_RECURSE StarterTemplateSource CONFIGURE_DEPENDS "${CMAKE_CURRENT_SOURCE_DIR}/src")
#
#add_library(
#		${PROJECT_NAME} INTERFACE
#)
#
#target_include_directories(
#		${PROJECT_NAME} INTERFACE
#		${StarterTemplateHeader}
#		${StarterTemplateSource}
#		$<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}/include>
#		$<INSTALL_INTERFACE:include/${PROJECT_NAME}-${PROJECT_VERSION}>
#)
#
#target_compile_features(
#		${PROJECT_NAME} INTERFACE
#		cxx_std_17
#)
#####################
# INTERFACE PROJECT END
#####################

# Code Coverage Configuration
add_library(coverage_config INTERFACE)
option(CODE_COVERAGE "Enable coverage reporting" OFF)
if(CODE_COVERAGE AND CMAKE_CXX_COMPILER_ID MATCHES "GNU|Clang")
	# Add required flags (GCC & LLVM/Clang)
	target_compile_options(
			coverage_config INTERFACE
			-O0        # no optimization
			-g         # generate debug info
			--coverage # sets all required flags
			)
	if(CMAKE_VERSION VERSION_GREATER_EQUAL 3.13)
		target_link_options(coverage_config INTERFACE --coverage)
	else()
		target_link_libraries(coverage_config INTERFACE --coverage)
	endif()
endif(CODE_COVERAGE AND CMAKE_CXX_COMPILER_ID MATCHES "GNU|Clang")

# for dependencies
include(cmake/CPM.cmake)

# add fmt support
CPMAddPackage(
		NAME fmt
		GIT_TAG master
		GITHUB_REPOSITORY fmtlib/fmt
		# create an installable target, this is necessary
		# https://github.com/fmtlib/fmt/blob/9cb347b4b2e80fc9fbf57b8621746663c3f870f6/CMakeLists.txt#L67
		OPTIONS
		"FMT_INSTALL ON"
		"FMT_TEST OFF"
)
target_link_libraries(
		${PROJECT_NAME}
		# PUBLIC -> can bt use in everywhere / PRIVATE -> .cpp file only / INTERFACE -> .hpp file only
		PUBLIC
		fmt
)

# todo: the git repo is incredibly large, you may need [this](https://github.com/cpm-cmake/CPM.cmake#cpm_source_cache).
CPMAddPackage(
		NAME nlohmann_json
		VERSION 3.9.1
		GITHUB_REPOSITORY nlohmann/json
		OPTIONS
		# https://github.com/nlohmann/json/blob/823801879ab9a99440b300a02b737c11e806d207/CMakeLists.txt#L34
		"JSON_Install ON"
		"JSON_BuildTests OFF"
)
target_link_libraries(
		${PROJECT_NAME}
		PUBLIC
		nlohmann_json
)

# being a cross-platform target, we enforce standards conformance on MSVC
target_compile_options(${PROJECT_NAME} PUBLIC "$<$<BOOL:${MSVC}>:/permissive->")

string(TOLOWER ${PROJECT_NAME}/version.h VERSION_HEADER_LOCATION)

# for packageProject below
#CPMAddPackage(
#		NAME PackageProject.cmake
#		GITHUB_REPOSITORY TheLartians/PackageProject.cmake
#		VERSION 1.6.0
#)
#CPMAddPackage("gh:TheLartians/PackageProject.cmake@1.6.0")
CPMAddPackage("gh:TheLartians/PackageProject.cmake#master")

packageProject(
		NAME ${PROJECT_NAME}
		VERSION ${PROJECT_VERSION}
		NAMESPACE ${PROJECT_NAME}
		BINARY_DIR ${PROJECT_BINARY_DIR}
		INCLUDE_DIR ${PROJECT_SOURCE_DIR}/include
		INCLUDE_DESTINATION include/${PROJECT_NAME}-${PROJECT_VERSION}
		VERSION_HEADER "${VERSION_HEADER_LOCATION}"
		DEPENDENCIES "galStarterTemplate"
)
