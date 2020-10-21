cmake_minimum_required(VERSION 2.8)
project(AprgUserAutomation C CXX)

set(OUTFILE ${PROJECT_NAME})

#Assign APRG Directory
set(APRG_DIR ${CMAKE_CURRENT_SOURCE_DIR}/../../)
set(APRG_USER_AUTO_DIR ${APRG_DIR}/AprgUserAutomation/AprgUserAutomation/)

#Assign Flags do not include -mwindows to make a console build
set(CMAKE_C_FLAGS "-Wall -Wextra -pedantic --coverage -std=c99")
set(CMAKE_CXX_FLAGS "-Wall -Wextra -pedantic --coverage -std=c++11")

#Include aprgCommon, this needs APRG Directory
include(${APRG_DIR}/AprgCommon/AprgCmakeInclude/AprgCommon.cmake)

#Include gTest, this needs APRG Directory
include(${APRG_DIR}/gtest-1.7.0/AprgCmakeInclude/gtest.cmake)

#Add files and directories
include(${APRG_USER_AUTO_DIR}/cmake/FilesAndDirectories.cmake)


add_executable(${OUTFILE} ${APRG_USER_AUTO_SOURCES_AND_TESTS})
include_directories(${APRG_USER_AUTO_INCLUDE_DIRECTORIES} ${GTEST_INCLUDE_DIRS})
target_link_libraries(${OUTFILE} gtest APRG_COMMON ${CMAKE_THREAD_LIBS_INIT})
add_test(${OUTFILE} ${OUTFILE})


