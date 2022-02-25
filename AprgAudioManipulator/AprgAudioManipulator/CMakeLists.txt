cmake_minimum_required(VERSION 3.16)
project(AprgAudioManipulator C CXX)

set(OUTFILE ${PROJECT_NAME})
#Comment out TEST_MODE to build static executable
set(TEST_MODE "ON")
#Assign APRG Directory
set(APRG_DIR ${CMAKE_CURRENT_SOURCE_DIR}/../../)
set(APRG_AUDIO_MANIPULATOR_DIR ${CMAKE_CURRENT_SOURCE_DIR})

#Assign Flags
include(${APRG_DIR}/AprgCMakeHelpers/CommonFlags.cmake)

#Assign Definitions
include(${APRG_DIR}/AprgCMakeHelpers/CommonDefinitions.cmake)

#Include gtest, this needs APRG Directory
include(${APRG_DIR}/gtest/AprgCmakeInclude/gtest.cmake)

#Include AprgCommon, this needs APRG Directory
include(${APRG_DIR}/AprgCommon/AprgCmakeInclude/AprgCommon.cmake)

#Include AprgAudio, this needs APRG Directory
include(${APRG_DIR}/AprgAudio/AprgCmakeInclude/AprgAudio.cmake)

#Add files and directories
include(${APRG_AUDIO_MANIPULATOR_DIR}/cmake/FilesAndDirectories.cmake)

if (TEST_MODE)
    add_executable(${OUTFILE} ${APRG_AUDIO_MANIPULATOR_SOURCES_AND_TESTS})
    include_directories(${APRG_AUDIO_MANIPULATOR_INCLUDE_DIRECTORIES} ${APRG_AUDIO_MANIPULATOR_TEST_INCLUDE_DIRECTORIES} ${GTEST_INCLUDE_DIRS})
    target_link_libraries(${OUTFILE} ${CMAKE_THREAD_LIBS_INIT} APRG_AUDIO APRG_COMMON gtest ${CMAKE_THREAD_LIBS_INIT})
    add_test(${OUTFILE} ${OUTFILE})
else()
    set(CMAKE_FIND_LIBRARY_SUFFIXES ".a")
    set(BUILD_SHARED_LIBRARIES OFF)
    set(CMAKE_EXE_LINKER_FLAGS "-static")
    add_executable(${OUTFILE} ${APRG_AUDIO_MANIPULATOR_SOURCES} ${APRG_AUDIO_MANIPULATOR_MAIN_SOURCES})
    include_directories(${APRG_AUDIO_MANIPULATOR_INCLUDE_DIRECTORIES})
    target_link_libraries(${OUTFILE} APRG_AUDIO APRG_COMMON)
endif()
