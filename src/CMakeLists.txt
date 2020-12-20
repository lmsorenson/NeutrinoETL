cmake_minimum_required(VERSION 3.5)

project(NeutrinoETL LANGUAGES CXX)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(glfw3 REQUIRED)
find_package(OpenGL REQUIRED)
find_package(Qt5 COMPONENTS Widgets LinguistTools REQUIRED)

set(TS_FILES NeutrinoETL_en_US.ts)

file(GLOB PROJECT_MOD_FILES
        main.cpp
        ui/mainwindow.cpp
        ui/mainwindow.h
        ui/mainwindow.ui
        ui/shaders/openglviewport.cpp
        ui/shaders/openglviewport.h
        ui/shaders/geometryengine.cpp
        ui/shaders/geometryengine.h
        ui/shaders/vertex.vsh
        ui/shaders/fragment.fsh
        ui/geometry/vertex.cpp
        ui/geometry/vertex.h
        ui/geometry/mesh.cpp
        ui/geometry/mesh.h
        ui/geometry/cube.cpp
        ui/geometry/cube.h
        models/neutrinoevent.cpp
        models/neutrinoevent.h
        models/neutrinotrack.cpp
        models/neutrinotrack.h
        models/neutrinopoint.cpp
        models/neutrinopoint.h
        strategies/deserialize.cpp
        strategies/deserialize.h
        strategies/neutrinoeventdeserializerv1.cpp
        strategies/neutrinoeventdeserializerv1.h
        ${TS_FILES}
        )

if(ANDROID)
  add_library(NeutrinoETL SHARED ${PROJECT_MOD_FILES})
else()
  add_executable(NeutrinoETL ${PROJECT_MOD_FILES})
endif()

target_link_libraries(NeutrinoETL PRIVATE Qt5::Widgets Qt5::Gui glfw OpenGL::GL)

qt5_create_translation(QM_FILES ${CMAKE_SOURCE_DIR} ${TS_FILES})
