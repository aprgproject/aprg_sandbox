#Assign AprgCommon directory, this needs aprg directory
set(APRG_BITMAP_MANIPULATOR_DIR ${APRG_DIR}/AprgBitmapManipulator/AprgBitmapManipulator/)

#Include APRG_COMMON files and directories
include(${APRG_BITMAP_MANIPULATOR_DIR}/cmake/FilesAndDirectories.cmake)

include_directories(${APRG_BITMAP_MANIPULATOR_INCLUDE_DIRECTORIES})
add_library(APRG_BITMAP_MANIPULATOR ${APRG_BITMAP_MANIPULATOR_SOURCES})
