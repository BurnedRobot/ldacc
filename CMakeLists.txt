cmake_minimum_required(VERSION 2.8)
project(LDACC)

set(CMAKE_REQUIRED_DEFINITIONS) # clear variable
set(CMAKE_CXX_COMPILER g++)
set(OLD_CMAKE_CXX_FLAGS ${CMAKE_CXX_FLAGS})
set(CMAKE_CXX_FLAGS "-g -std=c++11 -O2 -I /usr/local/boost_1_54_0 -fPIC ${OLD_CMAKE_CXX_FLAGS}")
set(EXECUTABLE_OUTPUT_PATH ${PROJECT_BINARY_DIR})

add_subdirectory(${PROJECT_SOURCE_DIR}/src)
