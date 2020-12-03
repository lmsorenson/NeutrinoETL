cmake_minimum_required(VERSION 3.5)

project(NeutrinoETL LANGUAGES CXX)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(Qt5 COMPONENTS Widgets LinguistTools REQUIRED)

set(TS_FILES NeutrinoETL_en_US.ts)

if(ANDROID)
  add_library(NeutrinoETL SHARED
    main.cpp
    src/ui/mainwindow.cpp
    src/ui/mainwindow.h
    src/ui/mainwindow.ui
    src/models/neutrinotrack.cpp
    src/models/neutrinotrack.h
    src/models/neutrinopoint.cpp
    src/models/neutrinopoint.h
    ${TS_FILES}
  )
else()
  add_executable(NeutrinoETL
    main.cpp
    src/ui/mainwindow.cpp
    src/ui/mainwindow.h
    src/ui/mainwindow.ui
    src/models/neutrinotrack.cpp
    src/models/neutrinotrack.h
    src/models/neutrinopoint.cpp
    src/models/neutrinopoint.h
    ${TS_FILES}
  )
endif()

target_link_libraries(NeutrinoETL PRIVATE Qt5::Widgets)

qt5_create_translation(QM_FILES ${CMAKE_SOURCE_DIR} ${TS_FILES})
