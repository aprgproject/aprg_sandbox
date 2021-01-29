cmake_minimum_required(VERSION 2.8)
project(BtsLogAnalyzer C CXX)

set(OUTFILE ${PROJECT_NAME})

#Assign APRG Directory
set(APRG_DIR ${CMAKE_CURRENT_SOURCE_DIR}/../../)
set(BTS_LOG_ANALYZER_DIR ${APRG_DIR}/BtsLogAnalyzer/BtsLogAnalyzer/)

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

#Include gTest, this needs APRG Directory
include(${APRG_DIR}/gtest/AprgCmakeInclude/gtest.cmake)

#Include AprgAlgorithm, this needs APRG Directory
include(${APRG_DIR}/AprgAlgorithm/AprgCmakeInclude/AprgAlgorithm.cmake)

#Include TcomToolsBackend, this needs APRG Directory
include(${APRG_DIR}/TcomTools/AprgCmakeInclude/TcomToolsBackend.cmake)

#Add files and directories
include(${BTS_LOG_ANALYZER_DIR}/cmake/FilesAndDirectories.cmake)

add_executable(${OUTFILE} ${BTS_LOG_ANALYZER_SOURCES_AND_TESTS})
include_directories(${BTS_LOG_ANALYZER_INCLUDE_DIRECTORIES} ${BTS_LOG_ANALYZER_TEST_INCLUDE_DIRECTORIES} ${GTEST_INCLUDE_DIRS})
target_link_libraries(${OUTFILE} TCOM_TOOLS_BACKEND APRG_ALGORITHM gtest ${CMAKE_THREAD_LIBS_INIT} APRG_COMMON)
add_test(${OUTFILE} ${OUTFILE})