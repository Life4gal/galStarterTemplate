project(my_awesome_application)

# Add an executable
add_executable(${PROJECT_NAME} src/main.cpp)

# Add fmt support
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

set(CMAKE_CXX_STANDARD 11)

if(NOT CMAKE_BUILD_TYPE AND NOT CMAKE_CONFIGURATION_TYPES)
	message("Setting build type to 'RelWithDebInfo' as none was specified.")
	set(
			CMAKE_BUILD_TYPE RelWithDebInfo
			CACHE STRING "Choose the type of build." FORCE
	)
	# Set the possible values of build type for cmake-gui
	set_property(
			CMAKE_BUILD_TYPE
			PROPERTY CACHE
			STRINGS "Debug" "Release" "MinSizeRel" "RelWithDebInfo"
	)
else()
	message("Current build type is: ${CMAKE_BUILD_TYPE}")
endif(NOT CMAKE_BUILD_TYPE AND NOT CMAKE_CONFIGURATION_TYPES)

if(CMAKE_BUILD_TYPE STREQUAL "Debug")
	target_compile_options(
			${PROJECT_NAME}
			PRIVATE
			$<$<CXX_COMPILER_ID:MSVC>:/MDd /Zi /Ob0 /Od /RTC1 /W4 /WX>
			$<$<NOT:$<CXX_COMPILER_ID:MSVC>>:-O0 -g -Wall -Wextra -Wpedantic -Werror>
	)
elseif(CMAKE_BUILD_TYPE STREQUAL "Release")
	target_compile_options(
			${PROJECT_NAME}
			PRIVATE
			$<$<CXX_COMPILER_ID:MSVC>:/MD /O2 /Ob2 /DNDEBUG /W4 /WX>
			$<$<NOT:$<CXX_COMPILER_ID:MSVC>>:-O3 -DNDEBUG -Wall -Wextra -Wpedantic -Werror>
	)
elseif(CMAKE_BUILD_TYPE STREQUAL "MinSizeRel")
	target_compile_options(
			${PROJECT_NAME}
			PRIVATE
			$<$<CXX_COMPILER_ID:MSVC>:/MD /O1 /Ob1 /DNDEBUG /W4 /WX>
			$<$<NOT:$<CXX_COMPILER_ID:MSVC>>:-Os -DNDEBUG -Wall -Wextra -Wpedantic -Werror>
	)
elseif(CMAKE_BUILD_TYPE STREQUAL "RelWithDebInfo")
	target_compile_options(
			${PROJECT_NAME}
			PRIVATE
			$<$<CXX_COMPILER_ID:MSVC>:/MD /Zi /O2 /Ob1 /DNDEBUG /W4 /WX>
			$<$<NOT:$<CXX_COMPILER_ID:MSVC>>:-O2 -g -DNDEBUG -Wall -Wextra -Wpedantic -Werror>
	)
else()
	message(FATAL_ERROR "Unsupported build type")
endif(CMAKE_BUILD_TYPE STREQUAL "Debug")
