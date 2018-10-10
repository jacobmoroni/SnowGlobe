cmake_minimum_required(VERSION 3.4)
project(SnowGlobe)

IF (NOT TARGET gtest)
    # Prevent GoogleTest from overriding our compiler/linker options
    # when building with Visual Studio
    set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
    add_subdirectory(libs/googletest)
ENDIF()

FIND_PACKAGE(Qt5Widgets)
FIND_PACKAGE(Qt5Gui)
FIND_PACKAGE(OpenSceneGraph REQUIRED COMPONENTS osgDB osgGA osgUtil osgViewer osgText)

INCLUDE_DIRECTORIES( ${OPENSCENEGRAPH_INCLUDE_DIRS} )

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED 1)
SET(CMAKE_INCLUDE_CURRENT_DIR ON)
SET(CMAKE_AUTOMOC ON)
SET(CMAKE_AUTOUIC ON)
SET(CMAKE_AUTORCC ON)

add_library(PhysicsLib STATIC
    physics.cpp
    physics.h
    vector.cpp
    vector.h
    sphere.cpp
    sphere.h
    )

SET(MYSOURCE
    main.cpp
    mainwindow.cpp
    mainwindow.h
    mainwindowform.ui
    osgwidget.h
    osgwidget.cpp
    sphereupdatecallback.cpp
    sphereupdatecallback.h
    )

set(TEST_NAME ${PROJECT_NAME}_UnitTest)

set( MYRESOURCES icons/icons.qrc)

add_executable(${PROJECT_NAME}
   ${MYSOURCE}
   ${MYRESOURCES}
   )

target_link_libraries(${PROJECT_NAME}
    ${OPENSCENEGRAPH_LIBRARIES}
    PhysicsLib
    Qt5::Widgets
    Qt5::Gui
    )

add_executable(${TEST_NAME}
    physics_unittests.cpp
    )

target_link_libraries(${TEST_NAME}
    PhysicsLib
    gtest
    gtest_main
    )
