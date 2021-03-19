#Assign AprgCommon directory, this needs aprg directory
set(DISPLAY_TABLE_DIR ${APRG_DIR}/DisplayTable/DisplayTable/)

#Include APRG_COMMON files and directories
include(${DISPLAY_TABLE_DIR}/cmake/FilesAndDirectories.cmake)

include_directories(${DISPLAY_TABLE_INCLUDE_DIRECTORIES})
add_library(DISPLAY_TABLE ${DISPLAY_TABLE_SOURCES})
