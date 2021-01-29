cmake_minimum_required(VERSION 2.8)
project(PerformanceAnalyzer C CXX)

set(OUTFILE ${PROJECT_NAME})

#Comment out TEST_MODE to build static executable
set(TEST_MODE "ON")

#Assign APRG Directory
set(APRG_DIR ${CMAKE_CURRENT_SOURCE_DIR}/../../)
set(PERFORMANCE_ANALYZER_DIR ${APRG_DIR}/PerformanceAnalyzer/PerformanceAnalyzer/)

#Assign Flags do not include -mwindows to make a console build
set(CMAKE_C_FLAGS "-Wall -Wextra -pedantic --coverage -std=c99")set(CMAKE_CXX_FLAGS "-Wall -Wextra -pedantic --coverage -std=c++11")
if(WIN32)
    #add -mwindows for windows GUI, do not add for console build
    #set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -mwindows")    #set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -mwindows")
endif()

#Assign Definitions
add_definitions(-DAPRG_DIR="${APRG_DIR}")
if(WIN32)
    #set for path of 7Zip for windows 32
    add_definitions(-DPATH_OF_7Z_EXECUTABLE="${APRG_DIR}AprgFileExtractor/7z32/7z.exe")
    add_definitions(-DPATH_OF_7Z_TEMP_FILE="${APRG_DIR}AprgFileExtractor/7z32/TempFile.txt")
endif()

#Include aprgCommon, this needs APRG Directory
include(${APRG_DIR}/AprgCommon/AprgCmakeInclude/AprgCommon.cmake)

#Include AprgAlgorithm, this needs APRG Directory
include(${APRG_DIR}/AprgAlgorithm/AprgCmakeInclude/AprgAlgorithm.cmake)

#Include AprgStatistics, this needs APRG Directory
include(${APRG_DIR}/AprgStatistics/AprgCmakeInclude/AprgStatistics.cmake)

#Include AprgFileExtractor, this needs APRG Directory
include(${APRG_DIR}/AprgFileExtractor/AprgCmakeInclude/AprgFileExtractor.cmake)

#Include TcomToolsBackend, this needs APRG Directory
include(${APRG_DIR}/TcomTools/AprgCmakeInclude/TcomToolsBackend.cmake)

#Include gTest, this needs APRG Directory
include(${APRG_DIR}/gtest/AprgCmakeInclude/gtest.cmake)

#Add files and directories
include(${PERFORMANCE_ANALYZER_DIR}/cmake/FilesAndDirectories.cmake)

add_executable(${OUTFILE} ${PERFORMANCE_ANALYZER_SOURCES_AND_TESTS})
include_directories(${PERFORMANCE_ANALYZER_INCLUDE_DIRECTORIES} ${GTEST_INCLUDE_DIRS})
target_link_libraries(APRG_FILE_EXTRACTOR APRG_COMMON APRG_ALGORITHM)
target_link_libraries(${OUTFILE} ${CMAKE_THREAD_LIBS_INIT} gtest APRG_COMMON APRG_ALGORITHM APRG_FILE_EXTRACTOR TCOM_TOOLS_BACKEND)
add_test(${OUTFILE} ${OUTFILE})