project(my_awesome_application)

# Add an executable
add_executable(${PROJECT_NAME} src/main.cpp)

set(CMAKE_CXX_STANDARD 11)

if(NOT CMAKE_BUILD_TYPE AND NOT CMAKE_CONFIGURATION_TYPES)
	message("Setting build type to 'RelWithDebInfo' as none was specified.")
	set(
			CMAKE_BUILD_TYPE RelWithDebInfo
			CACHE STRING "Choose the type of build." FORCE
	)
	set_property(
			CMAKE_BUILD_TYPE
			PROPERTY CACHE
			STRINGS "Debug" "Release" "MinSizeRel" "RelWithDebInfo"
	)
else()
	message("Current build type is: ${CMAKE_BUILD_TYPE}")
endif(NOT CMAKE_BUILD_TYPE AND NOT CMAKE_CONFIGURATION_TYPES)

target_compile_options(
		${PROJECT_NAME}
		PRIVATE

		$<$<CXX_COMPILER_ID:MSVC>:/W4 /WX>
		$<$<NOT:$<CXX_COMPILER_ID:MSVC>>:-Wall -Wextra -Wpedantic -Werror>

		$<$<NOT:$<CONFIG:Debug>>:$<$<CXX_COMPILER_ID:MSVC>:/DNDEBUG>$<$<NOT:$<CXX_COMPILER_ID:MSVC>>:-DNDEBUG>>

		$<$<CONFIG:Debug>: $<$<CXX_COMPILER_ID:MSVC>:/MDd /Zi /Ob0 /Od /RTC1> $<$<NOT:$<CXX_COMPILER_ID:MSVC>>:-O0 -g>>
		$<$<CONFIG:Release>: $<$<CXX_COMPILER_ID:MSVC>:/MD /O2 /Ob2> $<$<NOT:$<CXX_COMPILER_ID:MSVC>>:-O3>>
		$<$<CONFIG:RelWithDebInfo>: $<$<CXX_COMPILER_ID:MSVC>:/MD /Zi /O2 /Ob1> $<$<NOT:$<CXX_COMPILER_ID:MSVC>>:-O2 -g>>
		$<$<CONFIG:MinSizeRel>: $<$<CXX_COMPILER_ID:MSVC>:/MD /O1 /Ob1> $<$<NOT:$<CXX_COMPILER_ID:MSVC>>:-Os>>
)

# Add fmt support
CPMAddPackage(
		NAME fmt
		GIT_TAG master
		GITHUB_REPOSITORY fmtlib/fmt
		OPTIONS
		"FMT_PEDANTIC ON"
		"FMT_WERROR ON"
		"FMT_DOC OFF"
		# create an installable target, this is necessary
		# https://github.com/fmtlib/fmt/blob/9cb347b4b2e80fc9fbf57b8621746663c3f870f6/CMakeLists.txt#L67
		"FMT_INSTALL ON"
		"FMT_TEST OFF"
)

add_dependencies(
		${PROJECT_NAME}
		fmt
		STATIC_PART::MODULE1
		STATIC_PART::MODULE2
		SHARED_PART::MODULE1
)

target_link_libraries(
		${PROJECT_NAME}
		PRIVATE
		fmt
		STATIC_PART::MODULE1
		STATIC_PART::MODULE2
		SHARED_PART::MODULE1
)
