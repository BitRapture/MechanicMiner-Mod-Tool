cmake_minimum_required(VERSION 3.5)
project(brLayout)

set(${CMAKE_BUILD_PARALLEL_LEVEL} 8)
set(${CMAKE_CXX_STANDARD} 17)

add_library(brLayout 
    ${PROJECT_SOURCE_DIR}/src/element.cpp
    ${PROJECT_SOURCE_DIR}/src/layout.cpp
)

target_include_directories(brLayout PUBLIC
    ${PROJECT_SOURCE_DIR}/include
)