cmake_minimum_required(VERSION 3.15)
project(AbstractProgrammingProject)

set(CMAKE_CXX_STANDARD 20)

add_executable(project main.cpp utils/Trees/ExpTree.h utils/Dual.h)
add_executable(project_tests tests/main_tests.cpp)
