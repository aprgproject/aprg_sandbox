cmake_minimum_required(VERSION 2.8)
project(CrnccIdMapping C CXX)

set(OUTFILE ${PROJECT_NAME})

#Comment out TEST_MODE to build static executable
set(TEST_MODE "ON")

#Assign APRG Directory
set(APRG_DIR ${CMAKE_CURRENT_SOURCE_DIR}/../../)
set(CRNCCID_MAPPING_DIR ${CMAKE_CURRENT_SOURCE_DIR})

#Assign Flags
include(${APRG_DIR}/AprgCMakeHelpers/CommonFlags.cmake)

#Assign Definitions
include(${APRG_DIR}/AprgCMakeHelpers/CommonDefinitions.cmake)

#Include gtest, this needs APRG Directory
include(${APRG_DIR}/gtest/AprgCmakeInclude/gtest.cmake)

#Include AprgCommon, this needs APRG Directory
include(${APRG_DIR}/AprgCommon/AprgCmakeInclude/AprgCommon.cmake)

#Add files and directories
include(${CRNCCID_MAPPING_DIR}/cmake/FilesAndDirectories.cmake)

add_executable(${OUTFILE} ${CRNCCID_MAPPING_SOURCES_AND_TESTS})
include_directories(${CRNCCID_MAPPING_INCLUDE_DIRECTORIES} ${CRNCCID_MAPPING_TEST_INCLUDE_DIRECTORIES} ${GTEST_INCLUDE_DIRS})
target_link_libraries(${OUTFILE} ${CMAKE_THREAD_LIBS_INIT} APRG_COMMON gtest)
add_test(${OUTFILE} ${OUTFILE})
