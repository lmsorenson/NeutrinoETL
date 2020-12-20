cmake_minimum_required(VERSION 3.5)

project(NeutrinoETLTool)

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
set(ENV{PROJECT_MODS} ${PROJECT_MOD_FILES})

add_subdirectory(src)
add_subdirectory(test/ModelsUnitTests)