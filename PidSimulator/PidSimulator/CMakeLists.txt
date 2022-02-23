cmake_minimum_required(VERSION 3.20)
project(PidSimulator C CXX)

set(OUTFILE ${PROJECT_NAME})

#Comment out TEST_MODE to build static executable
set(TEST_MODE "ON")

#Assign APRG Directory
set(APRG_DIR ${CMAKE_CURRENT_SOURCE_DIR}/../../)
set(PID_SIMULATOR_DIR ${CMAKE_CURRENT_SOURCE_DIR})

#Assign Flags
include(${APRG_DIR}/AprgCMakeHelpers/CommonFlags.cmake)

#Assign Definitions
include(${APRG_DIR}/AprgCMakeHelpers/CommonDefinitions.cmake)

#Include gtest, this needs APRG Directory
include(${APRG_DIR}/gtest/AprgCmakeInclude/gtest.cmake)

#Include AprgCommon, this needs APRG Directory
include(${APRG_DIR}/AprgCommon/AprgCmakeInclude/AprgCommon.cmake)

#Include AprgBitmap, this needs APRG Directory
include(${APRG_DIR}/AprgBitmap/AprgCmakeInclude/AprgBitmap.cmake)

#Include AprgGeometry, this needs APRG Directory
include(${APRG_DIR}/AprgGeometry/AprgCmakeInclude/AprgGeometry.cmake)

#Include AprgAlgebra, this needs APRG Directory
include(${APRG_DIR}/AprgAlgebra/AprgCmakeInclude/AprgAlgebra.cmake)

#Include AprgGraph, this needs APRG Directory
include(${APRG_DIR}/AprgGraph/AprgCmakeInclude/AprgGraph.cmake)

#Add files and directories
include(${PID_SIMULATOR_DIR}/cmake/FilesAndDirectories.cmake)

if (TEST_MODE)
    add_executable(${OUTFILE} ${PID_SIMULATOR_SOURCES_AND_TESTS})
    include_directories(${PID_SIMULATOR_INCLUDE_DIRECTORIES} ${PID_SIMULATOR_TEST_INCLUDE_DIRECTORIES} ${GTEST_INCLUDE_DIRS})
    target_link_libraries(${OUTFILE} gtest APRG_GRAPH APRG_ALGEBRA APRG_GEOMETRY APRG_BITMAP APRG_COMMON ${CMAKE_THREAD_LIBS_INIT})  # add real time library
    add_test(${OUTFILE} ${OUTFILE})
else()
    set(CMAKE_FIND_LIBRARY_SUFFIXES ".a")
    set(BUILD_SHARED_LIBRARIES OFF)
    set(CMAKE_EXE_LINKER_FLAGS "-static")
    add_executable(${OUTFILE} ${PID_SIMULATOR_SOURCES} ${PID_SIMULATOR_MAIN_SOURCES})
    include_directories(${PID_SIMULATOR_INCLUDE_DIRECTORIES})
    target_link_libraries(${OUTFILE} gtest APRG_GRAPH APRG_ALGEBRA APRG_GEOMETRY APRG_BITMAP APRG_COMMON) # add real time library
endif()
