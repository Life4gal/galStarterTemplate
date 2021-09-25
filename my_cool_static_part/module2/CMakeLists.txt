project (
		cool_static_part_module2
		LANGUAGES CXX
)

set(
		LIBRARY_SOURCE
		src/hello2.cpp
)

add_library(
		${PROJECT_NAME}
		STATIC
		${LIBRARY_SOURCE}
)

add_library(
		STATIC_PART::MODULE2
		ALIAS
		${PROJECT_NAME}
)

target_include_directories(
		${PROJECT_NAME}
		PUBLIC
		${PROJECT_SOURCE_DIR}/include
)

# TEST
set(
		TEST_SOURCE
		test/test_hello2.cpp
)

add_executable(
		${PROJECT_NAME}_TEST
		${TEST_SOURCE}
)

target_link_libraries(
		${PROJECT_NAME}_TEST
		PRIVATE
		STATIC_PART::MODULE2
		gtest_main
)

# for gtest_discover_tests
include(GoogleTest)
gtest_discover_tests(${PROJECT_NAME}_TEST)
