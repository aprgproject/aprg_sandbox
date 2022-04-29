#Assign AprgCommon directory, this needs aprg directory
set(APRG_ALGORITHM_DIR ${APRG_DIR}/AprgAlgorithm/AprgAlgorithm/)

#Include APRG_COMMON files and directories
include(${APRG_ALGORITHM_DIR}/cmake/FilesAndDirectories.cmake)

include_directories(${APRG_ALGORITHM_INCLUDE_DIRECTORIES})
#add_library(APRG_ALGORITHM ${APRG_ALGORITHM_SOURCES}) # No CPP files