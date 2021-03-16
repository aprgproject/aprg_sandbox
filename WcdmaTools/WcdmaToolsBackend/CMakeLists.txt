cmake_minimum_required(VERSION 2.8)
project(WcdmaToolsBackend C CXX)

set(OUTFILE ${PROJECT_NAME})

#Assign APRG Directory
set(APRG_DIR ${CMAKE_CURRENT_SOURCE_DIR}/../../)
set(TCOM_TOOLS_BACKEND_DIR ${CMAKE_CURRENT_SOURCE_DIR})

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

#Add files and directories
include(${TCOM_TOOLS_BACKEND_DIR}/cmake/FilesAndDirectories.cmake)

add_executable(${OUTFILE} ${TCOM_TOOLS_BACKEND_SOURCES_AND_TESTS})
include_directories(${TCOM_TOOLS_BACKEND_INCLUDE_DIRECTORIES} ${TCOM_TOOLS_BACKEND_TEST_INCLUDE_DIRECTORIES} ${GTEST_INCLUDE_DIRS})
target_link_libraries(${OUTFILE} gtest ${CMAKE_THREAD_LIBS_INIT} APRG_COMMON APRG_ALGORITHM)
add_test(${OUTFILE} ${OUTFILE})
