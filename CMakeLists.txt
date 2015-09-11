cmake_minimum_required(VERSION 2.8)
set(CMAKE_CXX_FLAGS "-std=c++11 -Wall")

project(line_search)

add_executable(line_search main.cpp)

install(TARGETS line_search RUNTIME DESTINATION bin)
