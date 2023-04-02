cmake_minimum_required(VERSION 3.16)

#set project details
project(GoogleKickStart C CXX)
set(OUTFILE ${PROJECT_NAME})
set(GOOGLE_KICK_START_DIR ${CMAKE_CURRENT_SOURCE_DIR})

#Locate APRG Directory first because its used on other cmakes
include(${GOOGLE_KICK_START_DIR}/cmake/LocateAprgDirectory.cmake)

#Assign common flags, definitions and macros
include(${APRG_DIR}/AprgCMakeHelpers/CommonFlags.cmake)
include(${APRG_DIR}/AprgCMakeHelpers/CommonDefinitions.cmake)

#Include other projects
include(${APRG_DIR}/gtest/AprgCmakeInclude/gtest.cmake)
include(${APRG_DIR}/AprgCommon/AprgCmakeInclude/AprgCommon.cmake)

#Add files and directories
include(${GOOGLE_KICK_START_DIR}/cmake/FilesAndDirectories.cmake)

#Do final steps
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} ${APRG_COMPILER_FLAGS_FOR_DEBUG}")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${APRG_COMPILER_FLAGS_FOR_DEBUG}")
add_executable(${OUTFILE} ${GOOGLE_KICK_START_SOURCES_AND_TESTS})
include_directories(${GOOGLE_KICK_START_INCLUDE_DIRECTORIES} ${GOOGLE_KICK_START_TEST_INCLUDE_DIRECTORIES} ${GTEST_INCLUDE_DIRS})
target_link_libraries(${OUTFILE} ${CMAKE_THREAD_LIBS_INIT} APRG_COMMON gtest ${CMAKE_THREAD_LIBS_INIT} pthread)
add_test(${OUTFILE} ${OUTFILE})
include(${APRG_DIR}/AprgCMakeHelpers/LastStep.cmake)
