cmake_minimum_required (VERSION 3.2)

project (rw CXX)
SET(CMAKE_MODULE_PATH ${PROJECT_SOURCE_DIR}/cmakeModules)

set(glm_INCLUDE_DIR ${PROJECT_SOURCE_DIR}/dep/glm)
set(rapidjson_INCLUDE_DIR ${PROJECT_SOURCE_DIR}/dep/rapidjson/include)
set(tinyobjloader_INCLUDE_DIR ${PROJECT_SOURCE_DIR}/dep/tinyobjloader)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(GLUT REQUIRED)
find_package(PNG REQUIRED)
find_package(ALUT REQUIRED)

if(DEFAULTS_INITIALIZED)
else()
	message("initializing default config values...")

	set(DEFAULT_FLAGS "${PNG_DEFINITIONS} ${CMAKE_CXX_FLAGS}")
	if (CMAKE_CXX_COMPILER_ID STREQUAL "GNU")
		set(DEFAULT_FLAGS "-Wsuggest-override  -Wlogical-op -Wuseless-cast ${DEFAULT_FLAGS}" )
	endif()
	if (CMAKE_CXX_COMPILER_ID STREQUAL "Clang")
		set(DEFAULT_FLAGS "-std=c++11 ${DEFAULT_FLAGS}" )
	endif()
	# set default values for cached variables here
	if ((CMAKE_CXX_COMPILER_ID STREQUAL "GNU") OR (CMAKE_CXX_COMPILER_ID STREQUAL "Clang"))
		set(CMAKE_CXX_FLAGS "-Wextra -Wall -Wno-unused-parameter -Wuninitialized -Wswitch-default -Wfloat-equal -Wcast-qual -Wcast-align -fexceptions ${DEFAULT_FLAGS}" CACHE STRING "" FORCE)
	endif()
	if (CMAKE_BUILD_TYPE STREQUAL "")
		set(CMAKE_BUILD_TYPE "Debug" CACHE STRING "" FORCE)
	endif()
	message("default config values done.")
endif()

file(GLOB SRC_FILES ${PROJECT_SOURCE_DIR}/src/*.cpp)
file(GLOB INC_FILES ${PROJECT_SOURCE_DIR}/include/*.h)

#CLANG TOOLS STUFF:
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(CMAKE_CXX_USE_RESPONSE_FILE_FOR_INCLUDES 0) # needed by clang-check because it can't parse @response files
#fix-compile-cmds target
add_custom_target(fix-compile-cmds
    COMMAND ${CMAKE_COMMAND} -P "${CMAKE_SOURCE_DIR}/cmakeModules/fix_compile_cmds.cmake"
)

#clang-check target
add_custom_target(clang-check COMMAND clang-check -analyze -p "${CMAKE_BINARY_DIR}/compile_commands.json" ${SRC_FILES} WORKING_DIRECTORY ${CMAKE_BINARY_DIR} DEPENDS fix-compile-cmds)

#clang-tidy target
add_custom_target(clang-tidy COMMAND clang-tidy -p "${CMAKE_BINARY_DIR}/compile_commands.json" -fix "-checks=readability*,performance*,misc*,modernize*,cppcore*,cert-*"  ${SRC_FILES} WORKING_DIRECTORY ${CMAKE_BINARY_DIR} DEPENDS fix-compile-cmds)



include_directories(${PROJECT_SOURCE_DIR}/include ${GLUT_INCLUDE_DIR} ${PNG_INCLUDE_DIR} ${glm_INCLUDE_DIR} ${rapidjson_INCLUDE_DIR} ${tinyobjloader_INCLUDE_DIR} ${ALUT_INCLUDE_DIR})
add_executable(main ${SRC_FILES} ${INC_FILES})
target_link_libraries(main ${GLUT_LIBRARIES} ${PNG_LIBRARIES} ${ALUT_LIBRARIES})

#deps
#rapidjson - header only
#glm - header only
#tinyobjx  - needs fixing, because not header only

#build + run
#mkdir build
#cd build
#cmake .. -G"MinGW Makefiles" # for G++
#cmake .. -G"CodeBlocks - MinGW Makefiles" -DCMAKE_CXX_COMPILER=clang++ # zmienia toolchain
#mingw32-make
#cd ..
#build/main

set(DEFAULTS_INITIALIZED True CACHE STRING "If default cache values have already been set(ignore this value)" FORCE)
mark_as_advanced(DEFAULTS_INITIALIZED)