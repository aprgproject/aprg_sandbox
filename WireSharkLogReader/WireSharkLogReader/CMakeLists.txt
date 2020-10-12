cmake_minimum_required(VERSION 2.8)
project(WireSharkLogReader C CXX)

set(OUTFILE ${PROJECT_NAME})

#Assign APRG Directory
set(APRG_DIR ${CMAKE_CURRENT_SOURCE_DIR}/../../)
set(BtsLogAnalyzer_DIR ${APRG_DIR}/WireSharkLogReader/WireSharkLogReader/)

#Assign Flags
set(CMAKE_C_FLAGS "-Wall -Wextra -pedantic --coverage -std=c99 -mwindows")
set(CMAKE_CXX_FLAGS "-Wall -Wextra -pedantic --coverage -std=c++11 -mwindows")

#Include aprgCommon, this needs APRG Directory
include(${APRG_DIR}/AprgCommon/AprgCmakeInclude/AprgCommon.cmake)

#Include gTest, this needs APRG Directory
include(${APRG_DIR}/gtest-1.7.0/AprgCmakeInclude/gtest.cmake)

set(SOURCES
    #src/main.cpp
    src/WireSharkLogReader.cpp
    src/WireSharkLogReader.hpp
    tst/WireSharkLogReader_unit.cpp
)

add_executable(${OUTFILE} ${SOURCES})
include_directories(src/ ${GTEST_INCLUDE_DIRS})
target_link_libraries(${OUTFILE} gtest ${CMAKE_THREAD_LIBS_INIT} APRG_COMMON)
add_test(${OUTFILE} ${OUTFILE})
