#Assign AprgCommon directory, this needs aprg directory
set(SIMPLEST_DESIGN_TO_COPY_FOR_LIBRARIES_AND_PROGRAMS_DIR ${APRG_DIR}/SimplestDesignToCopyForLibrariesAndPrograms/SimplestDesignToCopyForLibrariesAndPrograms/)

#Include APRG_COMMON files and directories
include(${SIMPLEST_DESIGN_TO_COPY_FOR_LIBRARIES_AND_PROGRAMS_DIR}/cmake/FilesAndDirectories.cmake)

include_directories(${SIMPLEST_DESIGN_TO_COPY_FOR_LIBRARIES_AND_PROGRAMS_INCLUDE_DIRECTORIES})
add_library(SIMPLEST_DESIGN_TO_COPY_FOR_LIBRARIES_AND_PROGRAMS ${SIMPLEST_DESIGN_TO_COPY_FOR_LIBRARIES_AND_PROGRAMS_SOURCES})
