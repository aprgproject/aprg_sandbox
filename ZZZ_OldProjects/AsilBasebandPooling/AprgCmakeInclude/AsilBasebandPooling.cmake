#Assign AprgCommon directory, this needs aprg directory
set(ASIL_BASEBAND_POOLING_DIR ${APRG_DIR}/AsilBasebandPooling/AsilBasebandPooling/)

#Include APRG_COMMON files and directories
include(${ASIL_BASEBAND_POOLING_DIR}/cmake/FilesAndDirectories.cmake)

include_directories(${ASIL_BASEBAND_POOLING_INCLUDE_DIRECTORIES})
add_library(ASIL_BASEBAND_POOLING ${ASIL_BASEBAND_POOLING_SOURCES})
