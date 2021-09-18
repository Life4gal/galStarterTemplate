# Set the minimum version of CMake that can be used
# To find the cmake version run
# $ cmake --version
cmake_minimum_required(VERSION 3.12...3.20)

project(a-sub-project)

add_subdirectory(a-interface)
add_subdirectory(a-shared-library)
add_subdirectory(a-static-library)

add_subdirectory(application)
