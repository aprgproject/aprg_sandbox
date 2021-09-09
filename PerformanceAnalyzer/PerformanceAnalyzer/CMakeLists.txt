cmake_minimum_required(VERSION 2.8)
project(PerformanceAnalyzer C CXX)

set(OUTFILE ${PROJECT_NAME})

#Comment out TEST_MODE to build static executable
set(TEST_MODE "ON")

#Assign APRG Directory
set(APRG_DIR ${CMAKE_CURRENT_SOURCE_DIR}/../../)
set(PERFORMANCE_ANALYZER_DIR ${CMAKE_CURRENT_SOURCE_DIR})

#Assign Flags
include(${APRG_DIR}/AprgCMakeHelpers/CommonFlags.cmake)

#Assign Definitions
include(${APRG_DIR}/AprgCMakeHelpers/CommonDefinitions.cmake)
if(WIN32)
    #set for path of 7Zip for windows 32
    add_definitions(-DPATH_OF_7Z_EXECUTABLE="${APRG_DIR}AprgFileExtractor/7z32/7z.exe")
    add_definitions(-DPATH_OF_7Z_TEMP_FILE="${APRG_DIR}AprgFileExtractor/7z32/TempFile.txt")
endif()

#Include gtest, this needs APRG Directory
include(${APRG_DIR}/gtest/AprgCmakeInclude/gtest.cmake)

#Include AprgCommon, this needs APRG Directory
include(${APRG_DIR}/AprgCommon/AprgCmakeInclude/AprgCommon.cmake)

#Include AprgAlgorithm, this needs APRG Directory
include(${APRG_DIR}/AprgAlgorithm/AprgCmakeInclude/AprgAlgorithm.cmake)

#Include AprgStatistics, this needs APRG Directory
include(${APRG_DIR}/AprgStatistics/AprgCmakeInclude/AprgStatistics.cmake)

#Include AprgFileExtractor, this needs APRG Directory
include(${APRG_DIR}/AprgFileExtractor/AprgCmakeInclude/AprgFileExtractor.cmake)

#Include TcomToolsBackend, this needs APRG Directory
include(${APRG_DIR}/TcomTools/AprgCmakeInclude/TcomToolsBackend.cmake)

#Add files and directories
include(${PERFORMANCE_ANALYZER_DIR}/cmake/FilesAndDirectories.cmake)

add_executable(${OUTFILE} ${PERFORMANCE_ANALYZER_SOURCES_AND_TESTS})
include_directories(${PERFORMANCE_ANALYZER_INCLUDE_DIRECTORIES} ${GTEST_INCLUDE_DIRS})
target_link_libraries(APRG_FILE_EXTRACTOR APRG_ALGORITHM APRG_COMMON)
target_link_libraries(${OUTFILE} ${CMAKE_THREAD_LIBS_INIT} TCOM_TOOLS_BACKEND APRG_FILE_EXTRACTOR APRG_ALGORITHM APRG_COMMON gtest pthread)
add_test(${OUTFILE} ${OUTFILE})
