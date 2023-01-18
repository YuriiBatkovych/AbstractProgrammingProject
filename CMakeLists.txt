cmake_minimum_required(VERSION 3.15)

project(AbstractProgrammingProject)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
# Remove for compiler-specific features
set(CMAKE_CXX_EXTENSIONS OFF)


# clangd completion
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

include_directories(${CMAKE_SOURCE_DIR})
file(GLOB SOURCES "${CMAKE_SOURCE_DIR}/*.cpp")

add_executable(${PROJECT_NAME} ${SOURCES})