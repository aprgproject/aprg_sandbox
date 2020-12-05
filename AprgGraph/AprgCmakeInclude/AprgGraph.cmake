#Assign AprgCommon directory, this needs aprg directory
set(APRG_GRAPH_DIR ${APRG_DIR}/AprgAlgorithm/AprgAlgorithm/)

#Include APRG_COMMON files and directories
include(${APRG_GRAPH_DIR}/cmake/FilesAndDirectories.cmake)

include_directories(${APRG_GRAPH_INCLUDE_DIRECTORIES})
add_library(SIMPLEST_DESIGN_TO_COPY ${APRG_GRAPH_SOURCES})
