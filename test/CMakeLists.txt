cmake_minimum_required(VERSION 3.18.4)
project(tests)

set(CMAKE_CXX_STANDARD 17)

find_package(GTest CONFIG REQUIRED)

add_executable(${PROJECT_NAME} tests.cpp)

target_link_libraries(${PROJECT_NAME} GTest::gtest_main tree)