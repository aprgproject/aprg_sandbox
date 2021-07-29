#Assign AprgCommon directory, this needs aprg directory
set(APRG_MATH_SERIES_DIR ${APRG_DIR}/SimplestDesignToCopyForLibrariesAndPrograms/SimplestDesignToCopyForLibrariesAndPrograms/)

#Include APRG_COMMON files and directories
include(${APRG_MATH_SERIES_DIR}/cmake/FilesAndDirectories.cmake)

include_directories(${APRG_MATH_SERIES_INCLUDE_DIRECTORIES})
add_library(APRG_MATH_SERIES ${APRG_MATH_SERIES_SOURCES})
