#Assign AprgCommon directory, this needs aprg directory
set(APRG_AUDIO_DIR ${APRG_DIR}/AprgAudio/AprgAudio/)

#Include APRG_COMMON files and directories
include(${APRG_AUDIO_DIR}/cmake/FilesAndDirectories.cmake)

include_directories(${APRG_AUDIO_INCLUDE_DIRECTORIES})
add_library(APRG_AUDIO ${APRG_AUDIO_SOURCES})
