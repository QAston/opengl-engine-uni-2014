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
target_link_libraries(main PRIVATE FreeGLUT::freeglut)

find_package(glm CONFIG REQUIRED)
target_include_directories(main PRIVATE ${glm_INCLUDE_DIRS})

find_package(libpng CONFIG REQUIRED)
target_link_libraries(main PRIVATE png)

find_package(RapidJSON CONFIG REQUIRED)
target_include_directories(main PRIVATE ${RAPIDJSON_INCLUDE_DIRS})

find_package(tinyobjloader CONFIG REQUIRED)
target_link_libraries(main PRIVATE tinyobjloader::tinyobjloader)

include(FindPkgConfig)
pkg_check_modules(ALUT REQUIRED IMPORTED_TARGET freealut)
target_link_libraries(main PRIVATE PkgConfig::ALUT)