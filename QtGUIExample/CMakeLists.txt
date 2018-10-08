cmake_minimum_required(VERSION 3.4)
project(QtGUIExample)

FIND_PACKAGE(Qt5Widgets)
FIND_PACKAGE(Qt5Gui)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED 1)
SET(CMAKE_INCLUDE_CURRENT_DIR ON)
SET(CMAKE_AUTOMOC ON)
SET(CMAKE_AUTOUIC ON)
SET(CMAKE_AUTORCC ON)

SET(MYSOURCE
    main.cpp
    mainwindow.cpp
    mainwindow.h
    mainwindowform.ui
    outputwindow.h
    outputwindow.cpp
    outputwindow.ui
    stuffpanel.cpp
    stuffpanel.h
    stuffpanel.ui
    )

add_executable(${PROJECT_NAME}
    ${MYSOURCE}
    )

target_link_libraries(${PROJECT_NAME}
    Qt5::Widgets
    Qt5::Gui
)
