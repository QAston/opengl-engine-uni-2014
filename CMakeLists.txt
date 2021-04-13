cmake_minimum_required (VERSION 3.12)

project (rw VERSION 0.1
    DESCRIPTION "opengl training project"
    LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set_property(GLOBAL PROPERTY USE_FOLDERS ON)

add_executable(main src/aabbcollisionmgr.cpp
src/cube.cpp
src/displaymanagerglut.cpp
src/fpscamera.cpp
src/inputmanagerglut.cpp
src/keyframe.cpp
src/linearanimator.cpp
src/loadedobject.cpp
src/main.cpp
src/mover.cpp
src/objectmanagerglut.cpp
src/objloader.cpp
src/rwconfig.cpp
src/sceneloader.cpp
src/sceneobject.cpp
src/scenepos.cpp
src/soundsourceglut.cpp
src/worldobject.cpp
include/aabbcollisionmgr.h
include/animator.h
include/boundedobject.h
include/boundinfo.h
include/camera.h
include/collidingobject.h
include/constanimator.h
include/cube.h
include/displaymanager.h
include/displaymanagerglut.h
include/drawable.h
include/fpscamera.h
include/gameobject.h
include/inputlistener.h
include/inputmanager.h
include/inputmanagerglut.h
include/keyframe.h
include/linearanimator.h
include/loadedobject.h
include/movable.h
include/mover.h
include/objectdesc.h
include/objectmanager.h
include/objectmanagerglut.h
include/objloader.h
include/rwconfig.h
include/sceneloader.h
include/sceneobject.h
include/scenepos.h
include/soundsource.h
include/soundsourceglut.h
include/worldobject.h)
target_include_directories(main PUBLIC include)

find_package(FreeGLUT REQUIRED)
find_package(glm CONFIG REQUIRED)
find_package(libpng CONFIG REQUIRED)
find_package(RapidJSON CONFIG REQUIRED)
find_package(tinyobjloader CONFIG REQUIRED)
find_package(FreeALUT CONFIG REQUIRED)

target_link_libraries(main PRIVATE glm::glm tinyobjloader::tinyobjloader FreeALUT::alut INTERFACE RapidJSON::rapidjson )

if (TARGET FreeGLUT::freeglut_static)
    target_link_libraries(main PRIVATE FreeGLUT::freeglut_static)
elseif (TARGET FreeGLUT::freeglut)
    target_link_libraries(main PRIVATE FreeGLUT::freeglut)
endif()

if (TARGET png_static)
    target_link_libraries(main PRIVATE png_static)
elseif (TARGET png)
    target_link_libraries(main PRIVATE png)
endif()

if (${CMAKE_SYSTEM_NAME} STREQUAL "Linux")
    find_package(Threads REQUIRED)
    find_package(PkgConfig REQUIRED)
    pkg_check_modules(X11 REQUIRED IMPORTED_TARGET x11)
    add_library(X11::X11 ALIAS PkgConfig::X11)
    target_link_libraries(main PRIVATE Threads::Threads GLU ${CMAKE_DL_LIBS})
elseif(${CMAKE_SYSTEM_NAME} STREQUAL "Windows")
    target_link_libraries(main PRIVATE glu32)
endif()
