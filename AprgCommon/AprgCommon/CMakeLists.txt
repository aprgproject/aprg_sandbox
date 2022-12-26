cmake_minimum_required(VERSION 3.16)

#set project details
project(AprgCommon C CXX)
set(OUTFILE ${PROJECT_NAME})
set(APRG_COMMON_DIR ${CMAKE_CURRENT_SOURCE_DIR})

#Locate APRG Directory first because its used on other cmakes
include(${APRG_COMMON_DIR}/cmake/LocateAprgDirectory.cmake)

#Assign common flags, definitions and macros
include(${APRG_DIR}/AprgCMakeHelpers/CommonFlags.cmake)
include(${APRG_DIR}/AprgCMakeHelpers/CommonDefinitions.cmake)

#Include other projects
include(${APRG_DIR}/gtest/AprgCmakeInclude/gtest.cmake)

#Add files and directories
include(${APRG_COMMON_DIR}/cmake/FilesAndDirectories.cmake)

#Do final steps
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} ${APRG_COMPILER_FLAGS_FOR_DEBUG}")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${APRG_COMPILER_FLAGS_FOR_DEBUG}")
add_executable(${OUTFILE} ${APRG_COMMON_SOURCES_AND_TESTS})
include_directories(${APRG_COMMON_INCLUDE_DIRECTORIES} ${APRG_COMMON_TEST_INCLUDE_DIRECTORIES} ${GTEST_INCLUDE_DIRS})
target_link_libraries(${OUTFILE} gtest ${CMAKE_THREAD_LIBS_INIT})
add_test(${OUTFILE} ${OUTFILE})
include(${APRG_DIR}/AprgCMakeHelpers/LastStep.cmake)
