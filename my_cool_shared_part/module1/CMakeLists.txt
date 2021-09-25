project (
		cool_shared_part_module1
		LANGUAGES CXX
)

# WIN32 dll need export
# see also: http://gernotklingler.com/blog/creating-using-shared-libraries-different-compilers-different-operating-systems/
# see also: https://stackoverflow.com/questions/33062728/cmake-link-shared-library-on-windows/33297026
if(MSVC)
	add_compile_definitions(SHARED_NEED_EXPORT)
endif(MSVC)

set(
		LIBRARY_SOURCE
		src/hey1.cpp
)

add_library(
		${PROJECT_NAME}
		SHARED
		${LIBRARY_SOURCE}
)

add_library(
		SHARED_PART::MODULE1
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
		test/test_hey1.cpp
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
		SHARED_PART::MODULE1
		gtest_main
)

# for gtest_discover_tests
include(GoogleTest)
gtest_discover_tests(${PROJECT_NAME}_TEST)