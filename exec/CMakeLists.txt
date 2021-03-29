cmake_minimum_required(VERSION 3.12...3.17)

project(
		galStarterTemplateExec
		LANGUAGES CXX
)

file(GLOB_RECURSE google-test-source CONFIGURE_DEPENDS "${CMAKE_CURRENT_SOURCE_DIR}/google-test/*.cpp")
file(GLOB_RECURSE test-source CONFIGURE_DEPENDS "${CMAKE_CURRENT_SOURCE_DIR}/test/*.cpp")

add_executable(
		${PROJECT_NAME}
		${google-test-source}
		${test-source}
		main.cpp
)

set_target_properties(
		${PROJECT_NAME}
		PROPERTIES CXX_STANDARD 17
		OUTPUT_NAME "galStarterTemplateExec"
)

include(../cmake/CPM.cmake)

#CPMAddPackage("gh:jarro2783/cxxopts@2.2.1")
#CPMAddPackage("gh:jarro2783/cxxopts#master")
CPMAddPackage(
		NAME cxxopts
		GIT_TAG master
		# VERSION 2.2.1
		GITHUB_REPOSITORY jarro2783/cxxopts
		OPTIONS
		"CXXOPTS_BUILD_EXAMPLES off"
		"CXXOPTS_BUILD_TESTS off"
)
target_link_libraries(
		${PROJECT_NAME}
		PRIVATE
		cxxopts
)

include(cmake/google-test.cmake)
target_link_libraries(
		${PROJECT_NAME}
		PRIVATE
		gtest_main
)

CPMAddPackage(
		NAME galStarterTemplate
		SOURCE_DIR ${CMAKE_CURRENT_LIST_DIR}/..
)
target_link_libraries(
		${PROJECT_NAME}
		PRIVATE
		galStarterTemplate::galStarterTemplate
)
