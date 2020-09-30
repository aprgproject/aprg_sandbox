cmake_minimum_required(VERSION 2.8)
project(AprgFileExtractor C CXX)

set(OUTFILE ${PROJECT_NAME})

#Assign APRG Directory
set(APRG_DIR ${CMAKE_CURRENT_SOURCE_DIR}/../../)

#Assign Flags
set(CMAKE_C_FLAGS "-Wall -Wextra -pedantic --coverage -std=c99")
set(CMAKE_CXX_FLAGS "-Wall -Wextra -pedantic --coverage -std=c++11")

#Include gTest, this needs APRG Directory
include(${APRG_DIR}/gtest-1.7.0/AprgCmakeInclude/gtest.cmake)

#Include AprgCommon, this needs APRG Directory
include(${APRG_DIR}/AprgCommon/AprgCmakeInclude/AprgCommon.cmake)

set(SOURCES
    src/AprgFileExtractor.cpp
    src/AprgFileExtractor.hpp
    tst/AprgFileExtractor_unit.cpp
)

add_executable(${OUTFILE} ${SOURCES})
include_directories(src ${GTEST_INCLUDE_DIRS})
target_link_libraries(${OUTFILE} gtest APRG_COMMON ${CMAKE_THREAD_LIBS_INIT})
add_test(${OUTFILE} ${OUTFILE})
