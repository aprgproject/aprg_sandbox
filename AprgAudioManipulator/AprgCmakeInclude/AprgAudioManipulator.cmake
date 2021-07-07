#Assign AprgCommon directory, this needs aprg directory
set(APRG_AUDIO_MANIPULATOR_DIR ${APRG_DIR}/AprgAudioManipulator/AprgAudioManipulator/)

#Include APRG_COMMON files and directories
include(${APRG_AUDIO_MANIPULATOR_DIR}/cmake/FilesAndDirectories.cmake)

include_directories(${APRG_AUDIO_MANIPULATOR_INCLUDE_DIRECTORIES})
add_library(APRG_AUDIO_MANIPULATOR ${APRG_AUDIO_MANIPULATOR_SOURCES})
