cmake_minimum_required(VERSION 3.16)

#set project details
project(FesterRobot C CXX)
set(OUTFILE ${PROJECT_NAME})
set(FESTER_ROBOT_DIR ${CMAKE_CURRENT_SOURCE_DIR})

#Comment out TEST_MODE to build static executable, other cmakes check this
set(TEST_MODE "ON")

#Locate APRG Directory first because its used on other cmakes
include(${FESTER_ROBOT_DIR}/cmake/LocateAprgDirectory.cmake)

#Assign common flags, definitions and macros
include(${APRG_DIR}/AprgCMakeHelpers/CommonFlags.cmake)include(${APRG_DIR}/AprgCMakeHelpers/CommonDefinitions.cmake)

#Include other projects
include(${APRG_DIR}/gtest/AprgCmakeInclude/gtest.cmake)include(${APRG_DIR}/AprgCommon/AprgCmakeInclude/AprgCommon.cmake)
include(${APRG_DIR}/AprgLocalUserAutomation/AprgCmakeInclude/AprgLocalUserAutomation.cmake)

#Add files and directories
include(${FESTER_ROBOT_DIR}/cmake/FilesAndDirectories.cmake)

#Do final steps
if (TEST_MODE)
    set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} ${APRG_COMPILER_FLAGS_FOR_DEBUG}")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${APRG_COMPILER_FLAGS_FOR_DEBUG}")
    add_executable(${OUTFILE} ${FESTER_ROBOT_SOURCES_AND_TESTS})
    include_directories(${FESTER_ROBOT_INCLUDE_DIRECTORIES} ${FESTER_ROBOT_TEST_INCLUDE_DIRECTORIES} ${GTEST_INCLUDE_DIRS})
    target_link_libraries(${OUTFILE} ${CMAKE_THREAD_LIBS_INIT} APRG_LOCAL_USER_AUTOMATION APRG_COMMON gtest ${CMAKE_THREAD_LIBS_INIT})
    add_test(${OUTFILE} ${OUTFILE})
else()
    set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} ${APRG_COMPILER_FLAGS_FOR_RELEASE_WITH_SPEED}")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${APRG_COMPILER_FLAGS_FOR_RELEASE_WITH_SPEED}")
    set(CMAKE_EXE_LINKER_FLAGS ${APRG_LINKER_FLAGS_FOR_RELEASE_WITH_STRIP})
    add_executable(${OUTFILE} ${FESTER_ROBOT_SOURCES} ${FESTER_ROBOT_MAIN_SOURCES})
    include_directories(${FESTER_ROBOT_INCLUDE_DIRECTORIES})
    target_link_libraries(${OUTFILE} APRG_LOCAL_USER_AUTOMATION APRG_COMMON)
endif()
include(${APRG_DIR}/AprgCMakeHelpers/LastStep.cmake)