cmake_minimum_required(VERSION 3.0)

project(Calculator)

add_executable(calc main.cpp Calculator.cpp)

add_library(funcsin SHARED funcsin.cpp)

target_link_libraries(calc funcsin)
