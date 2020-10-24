#Assign AprgCommon directory, this needs aprg directory
set(SIMPLEST_DESIGN_TO_COPY_DIR ${APRG_DIR}/AprgAlgorithm/AprgAlgorithm/)

#Include APRG_COMMON files and directories
include(${SIMPLEST_DESIGN_TO_COPY_DIR}/cmake/FilesAndDirectories.cmake)

include_directories(${SIMPLEST_DESIGN_TO_COPY_INCLUDE_DIRECTORIES})
add_library(SIMPLEST_DESIGN_TO_COPY ${SIMPLEST_DESIGN_TO_COPY_SOURCES})
