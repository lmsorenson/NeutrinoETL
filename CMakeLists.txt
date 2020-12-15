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

if(ANDROID)
  add_library(NeutrinoETL SHARED
    main.cpp
    src/ui/mainwindow.cpp
    src/ui/mainwindow.h
    src/ui/mainwindow.ui
    src/ui/shaders/openglviewport.cpp
    src/ui/shaders/openglviewport.h
    src/ui/shaders/geometryengine.cpp
    src/ui/shaders/geometryengine.h
    src/ui/shaders/vertex.vsh
    src/ui/shaders/fragment.fsh
    src/ui/geometry/vertex.cpp
    src/ui/geometry/vertex.h
    src/ui/geometry/mesh.cpp
    src/ui/geometry/mesh.h
    src/ui/geometry/cube.cpp
    src/ui/geometry/cube.h
    src/models/neutrinotrack.cpp
    src/models/neutrinotrack.h
    src/models/neutrinopoint.cpp
    src/models/neutrinopoint.h
    src/strategies/deserialize.cpp
    src/strategies/deserialize.h
    src/strategies/neutrinoeventdeserializerv1.cpp
    src/strategies/neutrinoeventdeserializerv1.h
    ${TS_FILES}
  )
else()
  add_executable(NeutrinoETL
    main.cpp
    src/ui/mainwindow.cpp
    src/ui/mainwindow.h
    src/ui/mainwindow.ui
    src/ui/shaders/openglviewport.cpp
    src/ui/shaders/openglviewport.h
    src/ui/shaders/geometryengine.cpp
    src/ui/shaders/geometryengine.h
    src/ui/shaders/vertex.vsh
    src/ui/shaders/fragment.fsh
    src/ui/geometry/vertex.cpp
    src/ui/geometry/vertex.h
    src/ui/geometry/mesh.cpp
    src/ui/geometry/mesh.h
    src/ui/geometry/cube.cpp
    src/ui/geometry/cube.h
    src/models/neutrinoevent.cpp
    src/models/neutrinoevent.h
    src/models/neutrinotrack.cpp
    src/models/neutrinotrack.h
    src/models/neutrinopoint.cpp
    src/models/neutrinopoint.h
    src/strategies/deserialize.cpp
    src/strategies/deserialize.h
    src/strategies/neutrinoeventdeserializerv1.cpp
    src/strategies/neutrinoeventdeserializerv1.h
    ${TS_FILES}
  )
endif()

target_link_libraries(NeutrinoETL PRIVATE Qt5::Widgets Qt5::Gui glfw OpenGL::GL)

qt5_create_translation(QM_FILES ${CMAKE_SOURCE_DIR} ${TS_FILES})
