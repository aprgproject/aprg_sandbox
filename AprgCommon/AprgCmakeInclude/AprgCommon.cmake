#Assign Definitions
add_definitions(-DAPRG_DIR="${APRG_DIR}")
if(WIN32)
    add_definitions(-DOS_WINDOWS="WIN32")
endif()

#Assign AprgCommon directory, this needs aprg directory
set(APRG_COMMON_DIR ${APRG_DIR}/AprgCommon/AprgCommon/)

#Include APRG_COMMON files and directories
include(${APRG_COMMON_DIR}/cmake/FilesAndDirectories.cmake)

include_directories(${APRG_COMMON_INCLUDE_DIRECTORIES})
add_library(APRG_COMMON ${APRG_COMMON_SOURCES})
