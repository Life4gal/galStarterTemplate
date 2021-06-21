project(sub-project2)

set(
		google-test-source
		google-test/test1.cpp
		google-test/test2.cpp
		google-test/test3.cpp
		google-test/test4.cpp
		google-test/test5.cpp
		google-test/test6.cpp
		google-test/test7.cpp
		google-test/test8.cpp
		google-test/test9.cpp
		google-test/test10.cpp
)

add_executable(
		${PROJECT_NAME}
		${google-test-source}
		main.cpp
)

set_target_properties(
		${PROJECT_NAME}
		PROPERTIES CXX_STANDARD 17
		OUTPUT_NAME "subproject2"
)

include(cmake/google-test.cmake)
target_link_libraries(
		${PROJECT_NAME}
		PRIVATE
		gtest_main
)
