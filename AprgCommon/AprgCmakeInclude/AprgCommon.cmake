#Assign AprgCommon directory, needs aprg directory
set(APRG_COMMON_DIR ${APRG_DIR}/AprgCommon/AprgCommon/)

#Include APRG_COMMON files and directories
include(${APRG_COMMON_DIR}/cmake/FilesAndDirectories.cmake)

include_directories(${APRG_COMMON_INCLUDE_DIRECTORIES})
add_library(APRG_COMMON ${APRG_COMMON_SOURCES})