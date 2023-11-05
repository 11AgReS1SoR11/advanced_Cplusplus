cmake_minimum_required(VERSION 3.0)

project(Project)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall")

add_subdirectory(src)
add_subdirectory(tests)

configure_file(${CMAKE_CURRENT_SOURCE_DIR}/resources/res.xml ${CMAKE_BINARY_DIR}/resources/res.xml COPYONLY)
