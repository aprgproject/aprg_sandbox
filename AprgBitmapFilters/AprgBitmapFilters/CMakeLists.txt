cmake_minimum_required(VERSION 2.8)
project(AprgBitmapFilters C CXX)

set(OUTFILE ${PROJECT_NAME})

#Comment out TEST_MODE to build static executable
set(TEST_MODE "ON")

#Assign APRG Directory
set(APRG_DIR ${CMAKE_CURRENT_SOURCE_DIR}/../../)
set(APRG_BITMAP_FILTERS_DIR ${CMAKE_CURRENT_SOURCE_DIR})

#Assign Flags
include(${APRG_DIR}/AprgCMakeHelpers/CommonFlags.cmake)

#Assign Definitions
include(${APRG_DIR}/AprgCMakeHelpers/CommonDefinitions.cmake)

#Include gtest, this needs APRG Directory
include(${APRG_DIR}/gtest/AprgCmakeInclude/gtest.cmake)

#Include AprgCommon, this needs APRG Directory
include(${APRG_DIR}/AprgCommon/AprgCmakeInclude/AprgCommon.cmake)

#Include AprgAlgorithm, this needs APRG Directory
include(${APRG_DIR}/AprgAlgorithm/AprgCmakeInclude/AprgAlgorithm.cmake)

#Include AprgBitmap, this needs APRG Directory
include(${APRG_DIR}/AprgBitmap/AprgCmakeInclude/AprgBitmap.cmake)

#Include AprgGeometry, this needs APRG Directory
include(${APRG_DIR}/AprgGeometry/AprgCmakeInclude/AprgGeometry.cmake)

#Include AprgStatistics, this needs APRG Directory
include(${APRG_DIR}/AprgStatistics/AprgCmakeInclude/AprgStatistics.cmake)

#Add files and directories
include(${APRG_BITMAP_FILTERS_DIR}/cmake/FilesAndDirectories.cmake)

add_executable(${OUTFILE} ${APRG_BITMAP_FILTERS_SOURCES_AND_TESTS})
include_directories(${APRG_BITMAP_FILTERS_INCLUDE_DIRECTORIES} ${APRG_BITMAP_FILTERS_TEST_INCLUDE_DIRECTORIES} ${GTEST_INCLUDE_DIRS})
target_link_libraries(${OUTFILE} ${CMAKE_THREAD_LIBS_INIT} APRG_STATISTICS APRG_GEOMETRY APRG_ALGORITHM APRG_BITMAP APRG_COMMON gtest ${CMAKE_THREAD_LIBS_INIT})
add_test(${OUTFILE} ${OUTFILE})
