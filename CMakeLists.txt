project(gradientDescent)

cmake_minimum_required(VERSION 2.8)
set(CMAKE_CXX_FLAGS "-std=c++0x -Wall")

add_subdirectory(optimTools)

add_executable(gradientDescent example.cpp)

target_link_libraries(gradientDescent PRIVATE optimTools)


install(TARGETS gradientDescent RUNTIME DESTINATION bin)
