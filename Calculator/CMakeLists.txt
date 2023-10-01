cmake_minimum_required(VERSION 3.0)

project(Calculator)

add_executable(calc main.cpp Calculator.cpp Parser.cpp Sorter.cpp)

add_library(funcsin SHARED funcsin.cpp)
add_library(funccos SHARED funccos.cpp)
add_library(funcpow SHARED funcpow.cpp)

target_link_libraries(calc funcsin funccos funcpow)

add_subdirectory(ut)
