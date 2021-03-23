#compile cmds has dir separator escaping incompatibile with clang on windows, need to fix those
if(WIN32)
FILE(READ "${CMAKE_BINARY_DIR}/compile_commands.json" IN_VAR)

string(REGEX REPLACE "\\\\\\\\"
       "/" OUT_VAR
       ${IN_VAR})

file(WRITE "${CMAKE_BINARY_DIR}/compile_commands.json" ${OUT_VAR})
endif()