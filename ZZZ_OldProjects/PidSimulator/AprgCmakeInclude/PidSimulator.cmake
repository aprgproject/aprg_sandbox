#Assign AprgCommon directory, this needs aprg directory
set(PID_SIMULATOR_DIR ${APRG_DIR}/PidSimulator/PidSimulator/)

#Include APRG_COMMON files and directories
include(${PID_SIMULATOR_DIR}/cmake/FilesAndDirectories.cmake)

include_directories(${PID_SIMULATOR_INCLUDE_DIRECTORIES})
add_library(PID_SIMULATOR ${PID_SIMULATOR_SOURCES})
