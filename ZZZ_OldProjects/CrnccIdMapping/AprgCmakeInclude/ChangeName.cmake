#Assign AprgCommon directory, this needs aprg directory
set(SIMPLEST_DESIGN_TO_COPY_FOR_LIBRARIES_DIR ${APRG_DIR}/SimplestDesignToCopyForLibraries/SimplestDesignToCopyForLibraries/)

#Include APRG_COMMON files and directories
include(${SIMPLEST_DESIGN_TO_COPY_FOR_LIBRARIES_DIR}/cmake/FilesAndDirectories.cmake)

include_directories(${SIMPLEST_DESIGN_TO_COPY_FOR_LIBRARIES_INCLUDE_DIRECTORIES})
add_library(SIMPLEST_DESIGN_TO_COPY ${SIMPLEST_DESIGN_TO_COPY_FOR_LIBRARIES_SOURCES})
