cmake_minimum_required(VERSION 3.20)
project(matrix_unit_tests)

if(CMAKE_SYSTEM_PROCESSOR MATCHES arm64)
  message("SYSTEM PROCESSOR MATCHES arm64")
  set(CMAKE_CXX_COMPILER /Library/Developer/CommandLineTools/usr/bin/g++)
elseif(CMAKE_SYSTEM_PROCESSOR MATCHES x86_64)
  message("SYSTEM PROCESSOR MATCHES x86_64")
  if(CMAKE_SYSTEM_NAME MATCHES Linux)
    set(CMAKE_CXX_COMPILER /usr/bin/g++)
  else()
    set(CMAKE_CXX_COMPILER /usr/local/bin/g++)
  endif()
endif()

include(ExternalProject)
set(EXTERNAL_INSTALL_LOCATION ${CMAKE_BINARY_DIR}/external)
include(FetchContent)
FetchContent_Declare(googletest
googletest
  URL https://github.com/google/googletest/archive/ab669cad0eea4cbe59faf9a421ab01db30ebc13c.zip 
)
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/cmake/modules/")

set(CMAKE_CXX_FLAGS "-std=c++17 ${CMAKE_CXX_FLAGS}")
set(CMAKE_CXX_FLAGS_DEBUG "-std=c++17 -O0 -g -fprofile-arcs -ftest-coverage ${CMAKE_CXX_FLAGS_DEBUG}")

enable_testing()

if (NOT TARGET gtest_main)
  add_subdirectory(googletest)
endif ()


add_executable(matrix_test Matrix_tests.cc)

target_link_libraries(matrix_test s21_matrix_oop_source gtest gtest_main)

