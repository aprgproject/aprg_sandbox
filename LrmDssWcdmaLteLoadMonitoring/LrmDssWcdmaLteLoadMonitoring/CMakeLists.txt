cmake_minimum_required(VERSION 3.20)
project(LrmDssWcdmaLteLoadMonitoring C CXX)

set(OUTFILE ${PROJECT_NAME})
#Comment out TEST_MODE to build static executable
set(TEST_MODE "ON")
#Assign APRG Directory
set(APRG_DIR ${CMAKE_CURRENT_SOURCE_DIR}/../../)
set(LRM_DSS_WCDMA_LTE_LOAD_MONITORING_DIR ${CMAKE_CURRENT_SOURCE_DIR})

#Assign Flags
include(${APRG_DIR}/AprgCMakeHelpers/CommonFlags.cmake)

#Assign Definitions
include(${APRG_DIR}/AprgCMakeHelpers/CommonDefinitions.cmake)

#Include gtest, this needs APRG Directory
include(${APRG_DIR}/gtest/AprgCmakeInclude/gtest.cmake)

#Include AprgCommon, this needs APRG Directory
include(${APRG_DIR}/AprgCommon/AprgCmakeInclude/AprgCommon.cmake)

#Add files and directories
include(${LRM_DSS_WCDMA_LTE_LOAD_MONITORING_DIR}/cmake/FilesAndDirectories.cmake)

add_executable(${OUTFILE} ${LRM_DSS_WCDMA_LTE_LOAD_MONITORING_SOURCES_AND_TESTS})
include_directories(${LRM_DSS_WCDMA_LTE_LOAD_MONITORING_INCLUDE_DIRECTORIES} ${LRM_DSS_WCDMA_LTE_LOAD_MONITORING_TEST_INCLUDE_DIRECTORIES} ${GTEST_INCLUDE_DIRS})
target_link_libraries(${OUTFILE} ${CMAKE_THREAD_LIBS_INIT} APRG_COMMON gtest ${CMAKE_THREAD_LIBS_INIT})
add_test(${OUTFILE} ${OUTFILE})
