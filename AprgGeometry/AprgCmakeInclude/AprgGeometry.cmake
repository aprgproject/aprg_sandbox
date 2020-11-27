#Assign AprgCommon directory, this needs aprg directory
set(APRG_GEOMETRY_DIR ${APRG_DIR}/AprgGeometry/AprgGeometry/)

#Include APRG_COMMON files and directories
include(${APRG_GEOMETRY_DIR}/cmake/FilesAndDirectories.cmake)

include_directories(${APRG_GEOMETRY_INCLUDE_DIRECTORIES})
add_library(APRG_GEOMETRY ${APRG_GEOMETRY_SOURCES})
