cmake_minimum_required(VERSION 3.16)

#set project details
project(PerformanceAnalyzer C CXX)
set(OUTFILE ${PROJECT_NAME})
set(PERFORMANCE_ANALYZER_DIR ${CMAKE_CURRENT_SOURCE_DIR})

#Locate APRG Directory first because its used on other cmakes
include(${PERFORMANCE_ANALYZER_DIR}/cmake/LocateAprgDirectory.cmake)

#Assign common flags, definitions and macros
include(${APRG_DIR}/AprgCMakeHelpers/CommonFlags.cmake)include(${APRG_DIR}/AprgCMakeHelpers/CommonDefinitions.cmake)

#Assign specific definitions
if(WIN32)    #set for path of 7Zip for windows 32
    add_definitions(-DPATH_OF_7Z_EXECUTABLE="${APRG_DIR}AprgFileExtractor/7z32/7z.exe")
    add_definitions(-DPATH_OF_7Z_TEMP_FILE="${APRG_DIR}AprgFileExtractor/7z32/TempFile.txt")
endif()

#Include other projects
include(${APRG_DIR}/gtest/AprgCmakeInclude/gtest.cmake)
include(${APRG_DIR}/AprgCommon/AprgCmakeInclude/AprgCommon.cmake)
include(${APRG_DIR}/AprgAlgorithm/AprgCmakeInclude/AprgAlgorithm.cmake)
include(${APRG_DIR}/AprgStatistics/AprgCmakeInclude/AprgStatistics.cmake)
include(${APRG_DIR}/AprgFileExtractor/AprgCmakeInclude/AprgFileExtractor.cmake)
include(${APRG_DIR}/WcdmaTools/AprgCmakeInclude/WcdmaToolsBackend.cmake)
include(${APRG_DIR}/AprgGrepStringEvaluator/AprgCmakeInclude/AprgGrepStringEvaluator.cmake)

#Add files and directories
include(${PERFORMANCE_ANALYZER_DIR}/cmake/FilesAndDirectories.cmake)

#Do final steps
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} ${APRG_COMPILER_FLAGS_FOR_DEBUG}")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${APRG_COMPILER_FLAGS_FOR_DEBUG}")
add_executable(${OUTFILE} ${PERFORMANCE_ANALYZER_SOURCES_AND_TESTS})
include_directories(${PERFORMANCE_ANALYZER_INCLUDE_DIRECTORIES} ${GTEST_INCLUDE_DIRS})
target_link_libraries(APRG_FILE_EXTRACTOR APRG_COMMON)
target_link_libraries(${OUTFILE} ${CMAKE_THREAD_LIBS_INIT} WCDMA_TOOLS_BACKEND APRG_FILE_EXTRACTOR APRG_GREP_STRING_EVALUATOR APRG_COMMON gtest ${CMAKE_THREAD_LIBS_INIT})
add_test(${OUTFILE} ${OUTFILE})
include(${APRG_DIR}/AprgCMakeHelpers/LastStep.cmake)