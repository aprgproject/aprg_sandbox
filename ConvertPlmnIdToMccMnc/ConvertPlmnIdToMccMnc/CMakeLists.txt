cmake_minimum_required(VERSION 2.8)
project(ConvertPlmnIdToMccMnc C CXX)

set(OUTFILE ${PROJECT_NAME})

#Comment out TEST_MODE to build static executable
set(TEST_MODE "ON")

#Assign APRG Directory
set(APRG_DIR ${CMAKE_CURRENT_SOURCE_DIR}/../../)
set(CONVERT_PLMNID_TO_MCC_MNC_DIR ${CMAKE_CURRENT_SOURCE_DIR})

#Assign Flags
include(${APRG_DIR}/AprgCMakeHelpers/CommonFlags.cmake)

#Assign Definitions
include(${APRG_DIR}/AprgCMakeHelpers/CommonDefinitions.cmake)

#Include gtest, this needs APRG Directory
include(${APRG_DIR}/gtest/AprgCmakeInclude/gtest.cmake)

#Include AprgCommon, this needs APRG Directory
include(${APRG_DIR}/AprgCommon/AprgCmakeInclude/AprgCommon.cmake)

#Add files and directories
include(${CONVERT_PLMNID_TO_MCC_MNC_DIR}/cmake/FilesAndDirectories.cmake)

if (TEST_MODE)
    add_executable(${OUTFILE} ${CONVERT_PLMNID_TO_MCC_MNC_SOURCES_AND_TESTS})
    include_directories(${CONVERT_PLMNID_TO_MCC_MNC_INCLUDE_DIRECTORIES} ${CONVERT_PLMNID_TO_MCC_MNC_TEST_INCLUDE_DIRECTORIES} ${GTEST_INCLUDE_DIRS})
    target_link_libraries(${OUTFILE} ${CMAKE_THREAD_LIBS_INIT} APRG_COMMON gtest ${CMAKE_THREAD_LIBS_INIT})
    add_test(${OUTFILE} ${OUTFILE})
else()
    set(CMAKE_FIND_LIBRARY_SUFFIXES ".a")
    set(BUILD_SHARED_LIBRARIES OFF)
    set(CMAKE_EXE_LINKER_FLAGS "-static")
    add_executable(${OUTFILE} ${CONVERT_PLMNID_TO_MCC_MNC_SOURCES} ${CONVERT_PLMNID_TO_MCC_MNC_MAIN_SOURCES})
    include_directories(${CONVERT_PLMNID_TO_MCC_MNC_INCLUDE_DIRECTORIES})
    target_link_libraries(${OUTFILE} APRG_COMMON)
endif()
