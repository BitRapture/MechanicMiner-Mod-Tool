cmake_minimum_required(VERSION 3.5)
project(MM_ModTool)

set(${CMAKE_BUILD_PARALLEL_LEVEL} 8)
set(${CMAKE_CXX_STANDARD} 17)

add_executable(MM_ModTool 
    ${PROJECT_SOURCE_DIR}/src/raygui_impl.cpp
    ${PROJECT_SOURCE_DIR}/src/mod_tool.cpp
    ${PROJECT_SOURCE_DIR}/src/file_manager.cpp
    ${PROJECT_SOURCE_DIR}/src/info_file.cpp
    ${PROJECT_SOURCE_DIR}/src/mm_links_file.cpp
    ${PROJECT_SOURCE_DIR}/src/mm_assets_file.cpp
    ${PROJECT_SOURCE_DIR}/src/main.cpp
)

add_subdirectory(${PROJECT_SOURCE_DIR}/ext/raylib)
add_subdirectory(${PROJECT_SOURCE_DIR}/ext/raylib-cpp)
add_subdirectory(${PROJECT_SOURCE_DIR}/ext/layout)

target_link_libraries(MM_ModTool PUBLIC brLayout raylib raylib_cpp)

target_include_directories(MM_ModTool PUBLIC
    ${PROJECT_SOURCE_DIR}/include
    ${PROJECT_SOURCE_DIR}/ext/raylib/src
    ${PROJECT_SOURCE_DIR}/ext/raylib-cpp/include
    ${PROJECT_SOURCE_DIR}/ext/raygui/src
)