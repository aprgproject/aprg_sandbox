cmake_minimum_required(VERSION 2.8)
project(HeartTee C CXX)

set(OUTFILE ${PROJECT_NAME})

#Comment out TEST_MODE to build static executable
set(TEST_MODE "OFF")

#Assign APRG Directory
set(APRG_DIR ${CMAKE_CURRENT_SOURCE_DIR}/../../)

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

#Include gTest, this needs APRG Directory
include(${APRG_DIR}/gtest/AprgCmakeInclude/gtest.cmake)

set(SOURCES
    src/HeartTee/HeartTee.cpp
    src/HeartTee/HeartTee.hpp
    #mocks/SerialPortMock.hpp #removethis
    src/SerialPort/SerialPort.cpp
    src/SerialPort/SerialPort.hpp
    src/SqlConnect/SqlConnect.cpp
    src/SqlConnect/SqlConnect.hpp
    src/Fourier/Fourier.cpp
    src/Fourier/Fourier.hpp
)

set(MAIN_SOURCES
    src/main.cpp
)

set(TESTS
    tst/HeartTee_unit.cpp
)

set(INCLUDE_DIRECTORIES
    #mocks/#removethis
    src/HeartTee
    src/SerialPort
    src/SqlConnect
    src/Fourier
)

if (TEST_MODE)
    add_executable(${OUTFILE} ${SOURCES} ${TESTS})
    include_directories(${INCLUDE_DIRECTORIES} ${GTEST_INCLUDE_DIRS})
    target_link_libraries(${OUTFILE} gtest ${CMAKE_THREAD_LIBS_INIT} mysqlclient)
    add_test(${OUTFILE} ${OUTFILE})
else()
    set(CMAKE_FIND_LIBRARY_SUFFIXES ".a")
    set(BUILD_SHARED_LIBRARIES OFF)
    #set(CMAKE_EXE_LINKER_FLAGS "-static")
    add_executable(${OUTFILE} ${SOURCES} ${MAIN_SOURCES})
    include_directories(${INCLUDE_DIRECTORIES})
    target_link_libraries(${OUTFILE} mysqlclient)
endif()
