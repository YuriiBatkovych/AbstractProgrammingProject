cmake_minimum_required(VERSION 3.15)
project(AbstractProgrammingProject)

set(CMAKE_CXX_STANDARD 20)

set(Boost_INCLUDE_DIR D:/Boost/boost_1_78_0/boost_1_78_0/)
set(Boost_LIBRARY_DIR D:/Boost/boost_1_78_0/boost_1_78_0/)
find_package(Boost COMPONENTS REQUIRED)
include_directories(${Boost_INCLUDE_DIR})

add_executable(project main.cpp utils/ExpTree.h utils/Dual.h)
