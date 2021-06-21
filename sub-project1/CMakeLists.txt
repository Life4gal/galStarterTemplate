project(sub-project1)

set(
		SOURCE
		src/project_1.cpp
)

add_executable(
		${PROJECT_NAME}
		${SOURCE}
		main.cpp
)

set_target_properties(
		${PROJECT_NAME}
		PROPERTIES CXX_STANDARD 11
		OUTPUT_NAME "subproject1"
)

include_directories(usr/local/include/boost)

set(Boost_USE_STATIC_LIBS ON)

find_package(
		Boost COMPONENTS
		system
		filesystem
		thread
		regex
		REQUIRED
)

target_link_libraries(
		${PROJECT_NAME}
		pthread
		${Boost_SYSTEM_LIBRARY}
		${Boost_FILESYSTEM_LIBRARY}
		${Boost_THREAD_LIBRARY}
		${Boost_REGEX_LIBRARY}
)
