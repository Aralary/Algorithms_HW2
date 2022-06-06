cmake_minimum_required(VERSION 3.18.4)
project(Algorithms_HW2)

set(CMAKE_CXX_STANDARD 17)
set(SOURCES
        ${CMAKE_CURRENT_SOURCE_DIR}/sources/AVL_Tree.cpp
        )
add_library(tree STATIC ${SOURCES})

add_executable(${PROJECT_NAME} main.cpp)

target_include_directories(tree PUBLIC headers)
target_link_libraries(${PROJECT_NAME} tree)
add_subdirectory(test)