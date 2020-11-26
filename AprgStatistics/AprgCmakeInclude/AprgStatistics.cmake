#Assign AprgCommon directory, this needs aprg directory
set(APRG_STATISTICS_DIR ${APRG_DIR}/AprgAlgorithm/AprgAlgorithm/)

#Include APRG_COMMON files and directories
include(${APRG_STATISTICS_DIR}/cmake/FilesAndDirectories.cmake)

include_directories(${APRG_STATISTICS_INCLUDE_DIRECTORIES})
add_library(APRG_STATISTICS ${APRG_STATISTICS_SOURCES})
