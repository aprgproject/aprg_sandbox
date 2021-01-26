cmake_minimum_required(VERSION 2.8)
project(AprgCommon C CXX)

#set project name
set(OUTFILE ${PROJECT_NAME})

#Assign APRG Directory
set(APRG_DIR ${CMAKE_CURRENT_SOURCE_DIR}/../../)
set(APRG_COMMON_DIR ${APRG_DIR}/AprgCommon/AprgCommon/)

#Assign Flags
set(CMAKE_C_FLAGS "-Wall -Wextra -pedantic --coverage -std=c99")
set(CMAKE_CXX_FLAGS "-Wall -Wextra -pedantic --coverage -std=c++11")
if(WIN32)
    #add -mwindows for windows GUI, do not add for console build
    #set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -mwindows")
    #set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -mwindows")
endif()

#Assign Definitions
add_definitions(-DAPRG_DIR="${APRG_DIR}")
if(WIN32)
    add_definitions(-DOS_WINDOWS="WIN32")
endif()

#Include gTest, this needs APRG Directory
include(${APRG_DIR}/gtest/AprgCmakeInclude/gtest.cmake)

#Add files and directories
include(${APRG_COMMON_DIR}/cmake/FilesAndDirectories.cmake)

add_executable(${OUTFILE} ${APRG_COMMON_SOURCES_AND_TESTS})
include_directories(${APRG_COMMON_INCLUDE_DIRECTORIES} ${APRG_COMMON_TEST_INCLUDE_DIRECTORIES} ${GTEST_INCLUDE_DIRS})
target_link_libraries(${OUTFILE} gtest ${CMAKE_THREAD_LIBS_INIT})
add_test(${OUTFILE} ${OUTFILE})
