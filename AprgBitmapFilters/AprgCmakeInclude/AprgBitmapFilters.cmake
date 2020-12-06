#Assign AprgCommon directory, this needs aprg directory
set(APRG_BITMAP_FILTERS_DIR ${APRG_DIR}/AprgBitmapFilters/AprgBitmapFilters/)

#Include APRG_COMMON files and directories
include(${APRG_BITMAP_FILTERS_DIR}/cmake/FilesAndDirectories.cmake)

include_directories(${APRG_BITMAP_FILTERS_INCLUDE_DIRECTORIES})
add_library(APRG_BITMAP_FILTERS ${APRG_BITMAP_FILTERS_SOURCES})
