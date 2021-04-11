cmake_minimum_required(VERSION 3.13...3.20)

# set your project name
project(
		galStarterTemplate
		VERSION 1.0.3
		LANGUAGES CXX
)

include(cmake/StandardProjectSettings.cmake)
include(cmake/PreventInSourceBuilds.cmake)

option(ENABLE_IPO "Enable Interprocedural Optimization, aka Link Time Optimization (LTO)" TRUE)

option(ENABLE_OPTIONAL_MODULE "Enable optional module" TRUE)
option(ENABLE_COVERAGE "Enable coverage reporting for gcc/clang(only enable if ENABLE_OPTIONAL_MODULE)" TRUE)
option(ENABLE_SANITIZER_ADDRESS "Enable address sanitizer(only enable if ENABLE_OPTIONAL_MODULE)" TRUE)
option(ENABLE_SANITIZER_LEAK "Enable leak sanitizer(only enable if ENABLE_OPTIONAL_MODULE)" TRUE)
option(ENABLE_SANITIZER_THREAD "Enable thread sanitizer(only enable if ENABLE_OPTIONAL_MODULE)(Thread sanitizer does not work with Address and Leak sanitizer enabled)" FALSE)
option(ENABLE_SANITIZER_UNDEFINED_BEHAVIOR "Enable undefined behavior sanitizer(only enable if ENABLE_OPTIONAL_MODULE)" TRUE)
option(ENABLE_SANITIZER_MEMORY "Enable memory sanitizer(only enable if ENABLE_OPTIONAL_MODULE)(Memory sanitizer does not work with Address, Thread and Leak sanitizer enabled)" FALSE)
option(ENABLE_BUILD_WITH_TIME_TRACE "Enable -ftime-trace to generate time tracing .json files on clang(only enable if ENABLE_OPTIONAL_MODULE)" TRUE)

option(ENABLE_WARNING_MODULE "Enable warning module" TRUE)
option(ENABLE_WARNINGS_AS_ERRORS "Treat compiler warnings as errors(only enable if ENABLE_WARNING_MODULE)" TRUE)

#####################
# STANDARD PROJECT START
#####################

# evil source include
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

# evil source include
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

#####################
# OPTIONAL MODULE START
#####################

if (ENABLE_OPTIONAL_MODULE)
	if (CMAKE_CXX_COMPILER_ID MATCHES ".*Clang")
		if (ENABLE_BUILD_WITH_TIME_TRACE)
			target_compile_options(${PROJECT_NAME} INTERFACE -ftime-trace)
		endif ()
	endif ()

	# sanitizer options if supported by compiler
	include(cmake/Sanitizers.cmake)
	enable_sanitizers(${PROJECT_NAME})
endif ()

#####################
# OPTIONAL MODULE END
#####################


#####################
# WARNING MODULE START
#####################

if (ENABLE_WARNING_MODULE)
	include(cmake/CompilerWarnings.cmake)
	# standard compiler warnings
	set_project_warnings(${PROJECT_NAME})
endif ()

#####################
# WARNING MODULE END
#####################

#####################
# DEPENDENCIES MODULE START
#####################

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

#####################
# DEPENDENCIES MODULE END
#####################
