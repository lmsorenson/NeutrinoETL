cmake_minimum_required(VERSION 3.5)

project(PointTests LANGUAGES CXX)


find_package(Qt5Test REQUIRED)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
enable_testing()

add_executable(PointTests tst_pointtests.cpp)
add_test(NAME PointTests COMMAND PointTests)

target_link_libraries(PointTests PRIVATE Qt5::Test)

