cmake_minimum_required (VERSION 3.0)
project (rw CXX)


SET(CMAKE_MODULE_PATH ${PROJECT_SOURCE_DIR}/cmakeModules)

set(glm_INCLUDE_DIR ${PROJECT_SOURCE_DIR}/dep/glm)
set(rapidjson_INCLUDE_DIR ${PROJECT_SOURCE_DIR}/dep/rapidjson/include)
set(tinyobjloader_INCLUDE_DIR ${PROJECT_SOURCE_DIR}/dep/tinyobjloader)

find_package(GLUT REQUIRED)
find_package(PNG REQUIRED)
find_package(ALUT REQUIRED)


file(GLOB SRC_FILES ${PROJECT_SOURCE_DIR}/src/*.cpp)

include_directories(${PROJECT_SOURCE_DIR}/include ${GLUT_INCLUDE_DIR} ${PNG_INCLUDE_DIR} ${glm_INCLUDE_DIR} ${rapidjson_INCLUDE_DIR} ${tinyobjloader_INCLUDE_DIR} ${ALUT_})
add_compile_options("-Wextra;-Wall;-std=c++11;-fexceptions;-Wno-unused-parameter;-g;${PNG_DEFINITIONS}")
add_executable(main ${SRC_FILES})
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