#Project name
project(gradientDescent)

#Compiler flags
cmake_minimum_required(VERSION 2.8)
set(CMAKE_CXX_FLAGS "-std=c++0x -Wall")

#Folder containing optimization library
add_subdirectory(optimTools)

#Executable that calls optimization library
add_executable(gradientDescent example.cpp)

#Link to optimizatio library 
target_link_libraries(gradientDescent PRIVATE optimTools)

#Install the project
install(TARGETS gradientDescent RUNTIME DESTINATION bin)
