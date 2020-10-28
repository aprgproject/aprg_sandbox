cmake_minimum_required(VERSION 2.8)
project(AprgProcessFiles C CXX)

set(OUTFILE ${PROJECT_NAME})

#Assign APRG Directory
set(APRG_DIR ${CMAKE_CURRENT_SOURCE_DIR}/../../)
set(APRG_PROCESS_FILES_DIR ${APRG_DIR}/AprgProcessFiles/AprgProcessFiles/)

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

#Include aprgCommon, this needs APRG Directory
include(${APRG_DIR}/AprgCommon/AprgCmakeInclude/AprgCommon.cmake)

#Include aprgAlgorithm, this needs APRG Directory
include(${APRG_DIR}/AprgAlgorithm/AprgCmakeInclude/AprgAlgorithm.cmake)

#Include gTest, this needs APRG Directory
include(${APRG_DIR}/gtest-1.7.0/AprgCmakeInclude/gtest.cmake)

#Add files and directories
include(${APRG_PROCESS_FILES_DIR}/cmake/FilesAndDirectories.cmake)

add_executable(${OUTFILE} ${APRG_PROCESS_FILES_SOURCES_AND_TESTS})
include_directories(${APRG_PROCESS_FILES_INCLUDE_DIRECTORIES} ${APRG_PROCESS_FILES_TEST_INCLUDE_DIRECTORIES} ${GTEST_INCLUDE_DIRS})
target_link_libraries(${OUTFILE} gtest ${CMAKE_THREAD_LIBS_INIT} APRG_COMMON  APRG_ALGORITHM)
add_test(${OUTFILE} ${OUTFILE})
