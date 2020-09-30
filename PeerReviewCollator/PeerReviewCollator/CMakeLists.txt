cmake_minimum_required(VERSION 2.8)
project(PeerReviewCollator C CXX)

set(OUTFILE ${PROJECT_NAME})

#Assign APRG Directory
set(APRG_DIR ${CMAKE_CURRENT_SOURCE_DIR}/../../)

#Assign Flags do not include -mwindows to make a console build
set(CMAKE_C_FLAGS "-Wall -Wextra -pedantic --coverage -std=c99")
set(CMAKE_CXX_FLAGS "-Wall -Wextra -pedantic --coverage -std=c++11")

#Include aprgCommon, this needs APRG Directory
include(${APRG_DIR}/AprgCommon/AprgCmakeInclude/AprgCommon.cmake)

#Include gTest, this needs APRG Directory
include(${APRG_DIR}/gtest-1.7.0/AprgCmakeInclude/gtest.cmake)

set(SOURCES
    src/PeerReviewCollator.cpp
    src/PeerReviewCollator.hpp
    src/main.cpp
#    tst/PeerReviewCollator_unit.cpp
)

add_executable(${OUTFILE} ${SOURCES})
include_directories(src ${GTEST_INCLUDE_DIRS})
target_link_libraries(${OUTFILE} gtest ${CMAKE_THREAD_LIBS_INIT} APRG_COMMON )
#add_test(${OUTFILE} ${OUTFILE})
