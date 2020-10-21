#Assign APRG_USER_AUTO_DIR directory, this needs aprg directory
set(APRG_USER_AUTO_DIR ${APRG_DIR}/AprgUserAutomation/AprgUserAutomation/)

#Include APRG_COMMON files and directories
include(${APRG_USER_AUTO_DIR}/cmake/FilesAndDirectories.cmake)

include_directories(${APRG_USER_AUTO_INCLUDE_DIRECTORIES})
add_library(APRG_COMMON ${APRG_USER_AUTO_SOURCES})
