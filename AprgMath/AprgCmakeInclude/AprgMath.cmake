#Assign AprgCommon directory, this needs aprg directory
set(APRG_MATH_DIR ${APRG_DIR}/AprgMath/AprgMath/)

#Include APRG_COMMON files and directories
include(${APRG_MATH_DIR}/cmake/FilesAndDirectories.cmake)

include_directories(${APRG_MATH_INCLUDE_DIRECTORIES})
add_library(APRG_MATH ${APRG_MATH_SOURCES})
