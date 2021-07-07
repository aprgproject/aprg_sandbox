#Assign AprgCommon directory, this needs aprg directory
set(APRG_WAV_MANIPULATOR_DIR ${APRG_DIR}/AprgWavManipulator/AprgWavManipulator/)

#Include APRG_COMMON files and directories
include(${APRG_WAV_MANIPULATOR_DIR}/cmake/FilesAndDirectories.cmake)

include_directories(${APRG_WAV_MANIPULATOR_INCLUDE_DIRECTORIES})
add_library(APRG_WAV_MANIPULATOR ${APRG_WAV_MANIPULATOR_SOURCES})
