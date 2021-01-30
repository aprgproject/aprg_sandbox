cmake_minimum_required(VERSION 2.8)
project(HeartTee C CXX)

set(OUTFILE ${PROJECT_NAME})

#Comment out TEST_MODE to build static executable
set(TEST_MODE "OFF")

#Assign APRG Directory
set(APRG_DIR ${CMAKE_CURRENT_SOURCE_DIR}/../../)
set(HEART_TEE_DIR ${APRG_DIR}/HeartTee/HeartTee/)

#Assign Flags do not include -mwindows to make a console build
set(CMAKE_C_FLAGS "-Wall -Wextra -pedantic --coverage -std=c99")
set(CMAKE_CXX_FLAGS "-Wall -Wextra -pedantic --coverage -std=c++11")
if(WIN32)
    #add -mwindows for windows GUI, do not add for console build
    #set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -mwindows")
    #set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -mwindows")
endif()

#Assign Definitions
add_definitions(-DAPRG_DIR="${APRG_DIR}")

#Include gtest, this needs APRG Directory
include(${APRG_DIR}/gtest/AprgCmakeInclude/gtest.cmake)

#Add files and directories
include(${HEART_TEE_DIR}/cmake/FilesAndDirectories.cmake)

set(SPECIAL_INCLUDE_DIRECTORIES
    src/HeartTee
    src/SerialPort
    src/SqlConnect
    src/Fourier
)

if (TEST_MODE)
    add_executable(${OUTFILE} ${HEART_TEE_SOURCES_AND_TESTS})
    include_directories(${HEART_TEE_INCLUDE_DIRECTORIES} ${HEART_TEE_TEST_INCLUDE_DIRECTORIES} ${SPECIAL_INCLUDE_DIRECTORIES} ${GTEST_INCLUDE_DIRS})
    target_link_libraries(${OUTFILE} gtest ${CMAKE_THREAD_LIBS_INIT} mysqlclient)
    add_test(${OUTFILE} ${OUTFILE})
else()
    set(CMAKE_FIND_LIBRARY_SUFFIXES ".a")
    set(BUILD_SHARED_LIBRARIES OFF)
    #set(CMAKE_EXE_LINKER_FLAGS "-static")
    add_executable(${OUTFILE} ${HEART_TEE_SOURCES} ${HEART_TEE_MAIN_SOURCES})
    include_directories(${HEART_TEE_INCLUDE_DIRECTORIES} ${SPECIAL_INCLUDE_DIRECTORIES})
    target_link_libraries(${OUTFILE} mysqlclient)
endif()
