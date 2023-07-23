cmake_minimum_required(VERSION 3.20)
project(nd_matrix_oop)

set(CMAKE_CXX_STANDARD 17)

add_subdirectory(tests)
add_subdirectory(source)

option(CodeCoverage "CodeCoverage" OFF)
set(CMAKE_MODULE_PATH cmake/modules/)
include(CodeCoverage)

if (CMAKE_BUILD_TYPE MATCHES Debug)
    setup_target_for_coverage(${PROJECT_NAME}_coverage matrix_test coverage)
endif()
