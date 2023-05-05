#Assign AprgCommon directory, this needs aprg directory
set(APRG_LOCAL_SCREEN_MONITORING_DIR ${APRG_DIR}/AprgLocalScreenMonitoring/AprgLocalScreenMonitoring/)

#Include APRG_COMMON files and directories
include(${APRG_LOCAL_SCREEN_MONITORING_DIR}/cmake/FilesAndDirectories.cmake)

include_directories(${APRG_LOCAL_SCREEN_MONITORING_INCLUDE_DIRECTORIES})
add_library(APRG_LOCAL_SCREEN_MONITORING ${APRG_LOCAL_SCREEN_MONITORING_SOURCES})
