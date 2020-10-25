cmake_minimum_required(VERSION 2.8)
project(AprgGsl C CXX)

set(OUTFILE ${PROJECT_NAME})

#Comment out TEST_MODE to build static executable
set(TEST_MODE "ON")

#Assign APRG Directory
set(APRG_DIR ${CMAKE_CURRENT_SOURCE_DIR}/../../)
set(APRG_GSL_DIR ${APRG_DIR}/AprgGsl/AprgGsl/)

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

#Include aprgCommon, this needs APRG Directory
include(${APRG_DIR}/AprgCommon/AprgCmakeInclude/AprgCommon.cmake)
#Include aprgAlgorithm, this needs APRG Directory
include(${APRG_DIR}/AprgAlgorithm/AprgCmakeInclude/AprgAlgorithm.cmake)
#Include gTest, this needs APRG Directory
include(${APRG_DIR}/gtest-1.7.0/AprgCmakeInclude/gtest.cmake)

#Include gsl, this needs APRG Directory
include(${APRG_DIR}/gsl1.8/AprgCmakeInclude/Gsl.cmake)

#Add files and directories
include(${APRG_GSL_DIR}/cmake/FilesAndDirectories.cmake)

add_executable(${OUTFILE} ${APRG_GSL_SOURCES_AND_TESTS})
include_directories(${APRG_GSL_INCLUDE_DIRECTORIES} ${GTEST_INCLUDE_DIRS})
target_link_libraries(${OUTFILE} gtest APRG_COMMON APRG_ALGORITHM ${CMAKE_THREAD_LIBS_INIT} GSL GSLCBLAS)
add_test(${OUTFILE} ${OUTFILE})
