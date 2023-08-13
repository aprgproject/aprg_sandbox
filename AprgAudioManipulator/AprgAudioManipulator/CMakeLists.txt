cmake_minimum_required(VERSION 3.16)

#set project details
project(AprgAudioManipulator C CXX)
set(OUTFILE ${PROJECT_NAME})
set(APRG_AUDIO_MANIPULATOR_DIR ${CMAKE_CURRENT_SOURCE_DIR})

#Comment out TEST_MODE to build static executable, other cmakes check this
set(TEST_MODE "ON")

#Locate APRG Directory first because its used on other cmakes
include(${APRG_AUDIO_MANIPULATOR_DIR}/cmake/LocateAprgDirectory.cmake)

#Assign macros, common flags, definitions and other common steps
include(${APRG_DIR}/AprgCMakeHelpers/AllCommonSteps.cmake)

#Include other projects
include(${APRG_DIR}/gtest/AprgCmakeInclude/gtest.cmake)include(${APRG_DIR}/AprgCommon/AprgCmakeInclude/AprgCommon.cmake)
include(${APRG_DIR}/AprgAudio/AprgCmakeInclude/AprgAudio.cmake)

#Add files and directories
include(${APRG_AUDIO_MANIPULATOR_DIR}/cmake/FilesAndDirectories.cmake)

#Do final steps
if (TEST_MODE)
    set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} ${APRG_COMPILER_FLAGS_FOR_DEBUG}")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${APRG_COMPILER_FLAGS_FOR_DEBUG}")
    add_executable(${OUTFILE} ${APRG_AUDIO_MANIPULATOR_SOURCES_AND_TESTS})
    include_directories(${APRG_AUDIO_MANIPULATOR_INCLUDE_DIRECTORIES} ${APRG_AUDIO_MANIPULATOR_TEST_INCLUDE_DIRECTORIES} ${GTEST_INCLUDE_DIRS})
    target_link_libraries(${OUTFILE} APRG_AUDIO APRG_COMMON ${APRG_GTEST_DEPENDENCIES})
    add_test(${OUTFILE} ${OUTFILE})
else()
    set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} ${APRG_COMPILER_FLAGS_FOR_RELEASE_WITH_SPEED}")    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${APRG_COMPILER_FLAGS_FOR_RELEASE_WITH_SPEED}")
    set(CMAKE_EXE_LINKER_FLAGS ${APRG_LINKER_FLAGS_FOR_RELEASE_WITH_STRIP})
    add_executable(${OUTFILE} ${APRG_AUDIO_MANIPULATOR_SOURCES} ${APRG_AUDIO_MANIPULATOR_MAIN_SOURCES})
    include_directories(${APRG_AUDIO_MANIPULATOR_INCLUDE_DIRECTORIES})
    target_link_libraries(${OUTFILE} APRG_AUDIO APRG_COMMON)
endif()
include(${APRG_DIR}/AprgCMakeHelpers/LastStep.cmake)
