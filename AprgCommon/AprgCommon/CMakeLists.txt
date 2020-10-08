cmake_minimum_required(VERSION 2.8)
project(AprgCommon C CXX)

set(OUTFILE ${PROJECT_NAME})

#Assign APRG Directory
set(APRG_DIR ${CMAKE_CURRENT_SOURCE_DIR}/../../)
set(APRG_COMMON_DIR ${APRG_DIR}/AprgCommon/AprgCommon/)

#Assign Flags
set(CMAKE_C_FLAGS "-Wall -Wextra -pedantic --coverage -std=c99 -mwindows")
set(CMAKE_CXX_FLAGS "-Wall -Wextra -pedantic --coverage -std=c++11 -mwindows")

#Include gTest, this needs APRG Directory
include(${APRG_DIR}/gtest-1.7.0/AprgCmakeInclude/gtest.cmake)

#Add files and directories
include(${APRG_COMMON_DIR}/cmake/FilesAndDirectories.cmake)

add_executable(${OUTFILE} ${APRG_COMMON_SOURCES_AND_TESTS})
include_directories(${APRG_COMMON_INCLUDE_DIRECTORIES} ${GTEST_INCLUDE_DIRS})
target_link_libraries(${OUTFILE} gtest ${CMAKE_THREAD_LIBS_INIT})
add_test(${OUTFILE} ${OUTFILE})
