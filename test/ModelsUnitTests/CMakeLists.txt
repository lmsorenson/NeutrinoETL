cmake_minimum_required(VERSION 3.5)

project(ModelTests LANGUAGES CXX)

find_package(Qt5 COMPONENTS Widgets Test REQUIRED)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
enable_testing()

file(GLOB PROJECT_MOD_FILES
        ${CMAKE_SOURCE_DIR}/src/models/neutrinoevent.cpp
        ${CMAKE_SOURCE_DIR}/src/models/neutrinoevent.h
        ${CMAKE_SOURCE_DIR}/src/models/neutrinotrack.cpp
        ${CMAKE_SOURCE_DIR}/src/models/neutrinotrack.h
        ${CMAKE_SOURCE_DIR}/src/models/neutrinopoint.cpp
        ${CMAKE_SOURCE_DIR}/src/models/neutrinopoint.h)

add_executable(ModelTests
        ${PROJECT_MOD_FILES}
        main.cpp
        tst_eventtests.cpp
        tst_eventtests.h
        tst_tracktests.cpp
        tst_tracktests.h
        tst_pointtests.cpp
        tst_pointtests.h)

include_directories(${CMAKE_SOURCE_DIR}/src/)

add_test(NAME ModelTests COMMAND ModelTests)

target_link_libraries(ModelTests PRIVATE Qt5::Widgets Qt5::Test)

