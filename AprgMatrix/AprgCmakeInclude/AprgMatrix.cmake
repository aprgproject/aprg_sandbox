#Assign AprgMatrix directory, this needs aprg directory
set(APRG_MATRIX_DIR ${APRG_DIR}/AprgMatrix/AprgMatrix/)

#Include APRG_MATRIX files and directories
include(${APRG_MATRIX_DIR}/cmake/FilesAndDirectories.cmake)

include_directories(${APRG_MATRIX_INCLUDE_DIRECTORIES})

#No library because no cpp files
#add_library(APRG_MATRIX ${APRG_MATRIX_SOURCES})
