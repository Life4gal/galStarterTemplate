project (
		cool_static_part_module1
		LANGUAGES CXX
)

set(
		LIBRARY_SOURCE
		src/hello1.cpp
)

add_library(
		${PROJECT_NAME}
		STATIC
		${LIBRARY_SOURCE}
)

add_library(
		STATIC_PART::MODULE1
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
		test/test_hello1.cpp
)

add_executable(
		${PROJECT_NAME}_TEST
		${TEST_SOURCE}
)

add_dependencies(
		${PROJECT_NAME}_TEST
		${PROJECT_NAME}
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
