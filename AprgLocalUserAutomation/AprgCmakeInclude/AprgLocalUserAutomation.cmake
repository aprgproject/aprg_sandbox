#Assign AprgCommon directory, this needs aprg directory
set(APRG_LOCAL_USER_AUTOMATION_DIR ${APRG_DIR}/AprgLocalUserAutomation/AprgLocalUserAutomation/)

#Include APRG_COMMON files and directories
include(${APRG_LOCAL_USER_AUTOMATION_DIR}/cmake/FilesAndDirectories.cmake)

include_directories(${APRG_LOCAL_USER_AUTOMATION_INCLUDE_DIRECTORIES})
add_library(APRG_LOCAL_USER_AUTOMATION ${APRG_LOCAL_USER_AUTOMATION_SOURCES})
