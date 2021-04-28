#Assign AprgCommon directory, this needs aprg directory
set(APRG_GSL_DIR ${APRG_DIR}/AprgGsl/AprgGsl/)

#Include APRG_COMMON files and directories
include(${APRG_GSL_DIR}/cmake/FilesAndDirectories.cmake)

include_directories(${APRG_GSL_INCLUDE_DIRECTORIES})
add_library(APRG_GSL ${APRG_GSL_SOURCES})
