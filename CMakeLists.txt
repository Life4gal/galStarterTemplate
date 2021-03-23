cmake_minimum_required(VERSION 2.8.12...3.17)
project(
		StarterTemplate
		VERSION 0.1.0
		LANGUAGES CXX
)

#####################
# STANDARD PROJECT START
#####################
file(GLOB_RECURSE StarterTemplateHeader CONFIGURE_DEPENDS "${CMAKE_CURRENT_SOURCE_DIR}/include/*.hpp")
file(GLOB_RECURSE StarterTemplateSource CONFIGURE_DEPENDS "${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp")

add_library(
		${PROJECT_NAME}
		${StarterTemplateHeader}
		${StarterTemplateSource}
)

set_target_properties(${PROJECT_NAME} PROPERTIES CXX_STANDARD 17)

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

# being a cross-platform target, we enforce standards conformance on MSVC
target_compile_options(${PROJECT_NAME} PUBLIC "$<$<BOOL:${MSVC}>:/permissive->")

string(TOLOWER ${PROJECT_NAME}/version.h VERSION_HEADER_LOCATION)

# for CPMAddPackage below
include(cmake/CPM.cmake)

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
		DEPENDENCIES "StarterTemplate"
)
