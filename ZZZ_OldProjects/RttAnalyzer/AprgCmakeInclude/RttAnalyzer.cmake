#Assign AprgCommon directory, this needs aprg directory
set(RTT_ANALYZER_DIR ${APRG_DIR}/RttAnalyzer/RttAnalyzer/)

#Include APRG_COMMON files and directories
include(${RTT_ANALYZER_DIR}/cmake/FilesAndDirectories.cmake)

include_directories(${RTT_ANALYZER_INCLUDE_DIRECTORIES})
add_library(RTT_ANALYZER ${RTT_ANALYZER_SOURCES})
