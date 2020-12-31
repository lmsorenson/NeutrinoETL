cmake_minimum_required(VERSION 3.5)

project(UiTests LANGUAGES CXX)

find_package(glfw3)
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
        ${CMAKE_SOURCE_DIR}/src/ui/openglviewport.h
        ${CMAKE_SOURCE_DIR}/src/ui/geometry/geometryengine.cpp
        ${CMAKE_SOURCE_DIR}/src/ui/geometry/geometryengine.h
        ${CMAKE_SOURCE_DIR}/src/ui/geometry/cube.cpp
        ${CMAKE_SOURCE_DIR}/src/ui/geometry/cube.h
        ${CMAKE_SOURCE_DIR}/src/ui/geometry/mesh.cpp
        ${CMAKE_SOURCE_DIR}/src/ui/geometry/mesh.h
        ${CMAKE_SOURCE_DIR}/src/ui/geometry/vertex.cpp
        ${CMAKE_SOURCE_DIR}/src/ui/geometry/vertex.h)

add_executable(UiTests
        ${PROJECT_MOD_FILES}
        main.cpp
        tst_viewporttests.cpp
        tst_viewporttests.h
        )

include_directories(${CMAKE_SOURCE_DIR}/src/)

add_test(NAME ModelTests COMMAND UiTests)

target_link_libraries(UiTests PRIVATE Qt5::Widgets Qt5::Test Qt5::Gui glfw OpenGL::GL)

