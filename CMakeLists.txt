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

include(cmake/CPM.cmake)

CPMAddPackage(
		NAME fmt
		GIT_TAG master
		GITHUB_REPOSITORY fmtlib/fmt
		# create an installable target, this is necessary
		# https://github.com/fmtlib/fmt/blob/9cb347b4b2e80fc9fbf57b8621746663c3f870f6/CMakeLists.txt#L67
		OPTIONS "FMT_INSTALL YES"
)

CPMAddPackage(
		NAME nlohmann_json
		VERSION 3.9.1
		# the git repo is incredibly large, so we download the archived include directory
		URL https://github.com/nlohmann/json/releases/download/v3.9.1/include.zip
		URL_HASH SHA256=6bea5877b1541d353bd77bdfbdb2696333ae5ed8f9e8cc22df657192218cad91
		# https://github.com/nlohmann/json/blob/823801879ab9a99440b300a02b737c11e806d207/CMakeLists.txt#L34
		# why no effect
		OPTIONS "JSON_Install YES"
)

# todo: If the following code exists, everything work well, but...
# CMake Error: install(EXPORT "StarterTemplateTargets" ...) includes target "StarterTemplate" which requires target "nlohmann_json" that is not in any export set.
if(nlohmann_json_ADDED)
	add_library(nlohmann_json INTERFACE)
	target_include_directories(nlohmann_json SYSTEM INTERFACE ${nlohmann_json_SOURCE_DIR}/include)
endif()

target_link_libraries(
		${PROJECT_NAME}
		PUBLIC  # PUBLIC -> can bt use in everywhere / PRIVATE -> .cpp file only / INTERFACE -> .hpp file only
		fmt
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
		DEPENDENCIES "StarterTemplate"
)
