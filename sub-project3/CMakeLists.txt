project(sub-project3)

include(${CMAKE_MODULE_PATH}/StandardProjectSettings.cmake)
include(${CMAKE_MODULE_PATH}/PreventInSourceBuilds.cmake)

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

add_executable(
		${PROJECT_NAME}
		main.cpp
)

set_target_properties(
		${PROJECT_NAME}
		PROPERTIES CXX_STANDARD 17
		OUTPUT_NAME "subproject3"
)

if (ENABLE_OPTIONAL_MODULE)
	if (CMAKE_CXX_COMPILER_ID MATCHES ".*Clang")
		if (ENABLE_BUILD_WITH_TIME_TRACE)
			target_compile_options(${PROJECT_NAME} INTERFACE -ftime-trace)
		endif ()
	endif ()

	# sanitizer options if supported by compiler
	include(${CMAKE_MODULE_PATH}/Sanitizers.cmake)
	enable_sanitizers(${PROJECT_NAME})
endif ()

if (ENABLE_WARNING_MODULE)
	include(${CMAKE_MODULE_PATH}/CompilerWarnings.cmake)
	# standard compiler warnings
	set_project_warnings(${PROJECT_NAME})
endif ()

include(${CMAKE_MODULE_PATH}/CPM.cmake)

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
