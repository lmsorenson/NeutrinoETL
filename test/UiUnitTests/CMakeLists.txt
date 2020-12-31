cmake_minimum_required(VERSION 3.5)

project(UiTests LANGUAGES CXX)

find_package(glfw3)
if(NOT ${glfw3_FOUND})
    message("using submodule")
    add_subdirectory(../../packages/glfw ${CMAKE_BINARY_DIR}/glfw)
else()
    message("using found pacckage")
endif()

find_package(OpenGL REQUIRED)
find_package(Qt5 COMPONENTS Widgets Test REQUIRED)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
enable_testing()

file(GLOB PROJECT_MOD_FILES
        ${CMAKE_SOURCE_DIR}/src/ui/openglviewport.cpp
        ${CMAKE_SOURCE_DIR}/src/ui/openglviewport.h)

add_executable(UiTests
        ${PROJECT_MOD_FILES}
        main.cpp
        tst_viewporttests.cpp
        tst_viewporttests.h
        )

include_directories(${CMAKE_SOURCE_DIR}/src/)

add_test(NAME ModelTests COMMAND UiTests)

target_link_libraries(UiTests PRIVATE Qt5::Widgets Qt5::Test Qt5::Gui glfw OpenGL::GL)

