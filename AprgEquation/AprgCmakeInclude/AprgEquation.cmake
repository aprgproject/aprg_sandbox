#Assign AprgCommon directory, this needs aprg directory
set(APRG_EQUATION_DIR ${APRG_DIR}/AprgEquation/AprgEquation/)

#Include APRG_COMMON files and directories
include(${APRG_EQUATION_DIR}/cmake/FilesAndDirectories.cmake)

include_directories(${APRG_EQUATION_INCLUDE_DIRECTORIES})
add_library(APRG_EQUATION ${APRG_EQUATION_SOURCES})
