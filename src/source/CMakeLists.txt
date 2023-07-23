cmake_minimum_required(VERSION 3.20)
project(nd_matrix_oop_source)

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
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_CXX_STANDARD 17)

set(CMAKE_CXX_FLAGS "-std=c++17 -Wall -Werror -Wextra ${CMAKE_CXX_FLAGS}")
set(CMAKE_CXX_FLAGS_DEBUG "-std=c++17 -O0 -Wall -Werror -Wextra -g -fprofile-arcs -ftest-coverage ${CMAKE_CXX_FLAGS_DEBUG}")
 
set(HEADER nd_matrix_oop.h)
set(SOURCE nd_matrix_oop.cc)
  
add_library(${PROJECT_NAME} STATIC ${SOURCE} ${HEADER})

set_target_properties(${PROJECT_NAME} PROPERTIES OUTPUT_NAME "nd_matrix_oop")
set_target_properties(${PROJECT_NAME} PROPERTIES PREFIX "")