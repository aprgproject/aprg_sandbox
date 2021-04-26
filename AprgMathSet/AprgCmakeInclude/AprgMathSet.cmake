#Assign AprgCommon directory, this needs aprg directory
set(APRG_MATH_SET_DIR ${APRG_DIR}/AprgMathSet/AprgMathSet/)

#Include APRG_COMMON files and directories
include(${APRG_MATH_SET_DIR}/cmake/FilesAndDirectories.cmake)

include_directories(${APRG_MATH_SET_INCLUDE_DIRECTORIES})
add_library(APRG_MATH_SET ${APRG_MATH_SET_SOURCES})
