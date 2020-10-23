#Assign AprgCommon directory, this needs aprg directory
set(APRG_PROCESS_FILES_DIR ${APRG_DIR}/AprgProcessFiles/AprgProcessFiles/)

#Include APRG_COMMON files and directories
include(${APRG_PROCESS_FILES_DIR}/cmake/FilesAndDirectories.cmake)

include_directories(${APRG_PROCESS_FILES_INCLUDE_DIRECTORIES})
add_library(APRG_PROCESS_FILES ${APRG_PROCESS_FILES_SOURCES})
