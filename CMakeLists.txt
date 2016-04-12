cmake_minimum_required (VERSION 3.0)

project (rw CXX)
SET(CMAKE_MODULE_PATH ${PROJECT_SOURCE_DIR}/cmakeModules)

set(glm_INCLUDE_DIR ${PROJECT_SOURCE_DIR}/dep/glm)
set(rapidjson_INCLUDE_DIR ${PROJECT_SOURCE_DIR}/dep/rapidjson/include)
set(tinyobjloader_INCLUDE_DIR ${PROJECT_SOURCE_DIR}/dep/tinyobjloader)

find_package(GLUT REQUIRED)
find_package(PNG REQUIRED)
find_package(ALUT REQUIRED)

if(DEFAULTS_INITIALIZED)
else()
	message("initializing default config values...")
	# set default values for cached variables here
	set(CMAKE_CXX_FLAGS "-Wextra;-Wall;-std=c++11;-fexceptions;-Wno-unused-parameter;${PNG_DEFINITIONS}" CACHE STRING "" FORCE)
	set(CMAKE_BUILD_TYPE "Debug" CACHE STRING "" FORCE)
	message("default config values done.")
endif()

file(GLOB SRC_FILES ${PROJECT_SOURCE_DIR}/src/*.cpp)
file(GLOB INC_FILES ${PROJECT_SOURCE_DIR}/include/*.h)

include_directories(${PROJECT_SOURCE_DIR}/include ${GLUT_INCLUDE_DIR} ${PNG_INCLUDE_DIR} ${glm_INCLUDE_DIR} ${rapidjson_INCLUDE_DIR} ${tinyobjloader_INCLUDE_DIR} ${ALUT_})
add_executable(main ${SRC_FILES} ${INC_FILES})
target_link_libraries(main ${GLUT_LIBRARIES} ${PNG_LIBRARIES} ${ALUT_LIBRARIES})

#deps
#rapidjson - header only
#glm - header only
#tinyobjx  - needs fixing, because not header only

#build + run
#mkdir build
#cd build
#cmake .. -G"MinGW Makefiles"
#mingw32-make
#cd ..
#build/main

set(DEFAULTS_INITIALIZED True CACHE STRING "If default cache values have already been set(ignore this value)" FORCE)