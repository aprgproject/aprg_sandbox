cmake_minimum_required(VERSION 3.20)
project(AprgGraph C CXX)

set(OUTFILE ${PROJECT_NAME})
#Comment out TEST_MODE to build static executable
set(TEST_MODE "ON")
#Assign APRG Directory
set(APRG_DIR ${CMAKE_CURRENT_SOURCE_DIR}/../../)
set(APRG_GRAPH_DIR ${CMAKE_CURRENT_SOURCE_DIR})

#Assign Flags
include(${APRG_DIR}/AprgCMakeHelpers/CommonFlags.cmake)

#Assign Definitions
include(${APRG_DIR}/AprgCMakeHelpers/CommonDefinitions.cmake)

#Include AprgCommon, this needs APRG Directory
include(${APRG_DIR}/AprgCommon/AprgCmakeInclude/AprgCommon.cmake)

#Include gtest, this needs APRG Directory
include(${APRG_DIR}/gtest/AprgCmakeInclude/gtest.cmake)

#Include AprgAlgebra, this needs APRG Directory
include(${APRG_DIR}/AprgAlgebra/AprgCmakeInclude/AprgAlgebra.cmake)

#Include AprgGeometry, this needs APRG Directory
include(${APRG_DIR}/AprgGeometry/AprgCmakeInclude/AprgGeometry.cmake)

#Include AprgBitmap, this needs APRG Directory
include(${APRG_DIR}/AprgBitmap/AprgCmakeInclude/AprgBitmap.cmake)

#Add files and directories
include(${APRG_GRAPH_DIR}/cmake/FilesAndDirectories.cmake)

add_executable(${OUTFILE} ${APRG_GRAPH_SOURCES_AND_TESTS})
include_directories(${APRG_GRAPH_INCLUDE_DIRECTORIES} ${APRG_GRAPH_TEST_INCLUDE_DIRECTORIES} ${GTEST_INCLUDE_DIRS})
target_link_libraries(${OUTFILE} gtest APRG_BITMAP APRG_GEOMETRY APRG_ALGEBRA APRG_COMMON ${CMAKE_THREAD_LIBS_INIT})
add_test(${OUTFILE} ${OUTFILE})
