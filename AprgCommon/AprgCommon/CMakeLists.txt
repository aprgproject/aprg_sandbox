cmake_minimum_required(VERSION 2.8)
project(AprgCommon C CXX)

#set project name
set(OUTFILE ${PROJECT_NAME})

#Assign APRG Directory
set(APRG_DIR ${CMAKE_CURRENT_SOURCE_DIR}/../../)
set(APRG_COMMON_DIR ${CMAKE_CURRENT_SOURCE_DIR})

#Assign Flags
include(${APRG_DIR}/AprgCMakeHelpers/CommonFlags.cmake)

#Assign Definitions
include(${APRG_DIR}/AprgCMakeHelpers/CommonDefinitions.cmake)

#Include gtest, this needs APRG Directory
include(${APRG_DIR}/gtest/AprgCmakeInclude/gtest.cmake)

#Add files and directories
include(${APRG_COMMON_DIR}/cmake/FilesAndDirectories.cmake)

add_executable(${OUTFILE} ${APRG_COMMON_SOURCES_AND_TESTS})
include_directories(${APRG_COMMON_INCLUDE_DIRECTORIES} ${APRG_COMMON_TEST_INCLUDE_DIRECTORIES} ${GTEST_INCLUDE_DIRS})
target_link_libraries(${OUTFILE} gtest ${CMAKE_THREAD_LIBS_INIT})
add_test(${OUTFILE} ${OUTFILE})
