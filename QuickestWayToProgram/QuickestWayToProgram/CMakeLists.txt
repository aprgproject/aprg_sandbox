cmake_minimum_required(VERSION 3.16)

#set project details
project(QuickestWayToProgram C CXX)
set(OUTFILE ${PROJECT_NAME})
set(QUICKEST_WAY_TO_PROGRAM_DIR ${CMAKE_CURRENT_SOURCE_DIR})

#Locate APRG Directory first because its used on other cmakes
get_filename_component(ABSOLUTE_CURRENT_DIR "${CMAKE_CURRENT_LIST_DIR}" ABSOLUTE)
get_filename_component(CURRENT_DIR_NAME "$${ABSOLUTE_CURRENT_DIR}" NAME)
while(NOT ${CURRENT_DIR_NAME} MATCHES "APRG")
    get_filename_component(ABSOLUTE_CURRENT_DIR "${ABSOLUTE_CURRENT_DIR}/.." ABSOLUTE)
    get_filename_component(CURRENT_DIR_NAME "$${ABSOLUTE_CURRENT_DIR}" NAME)
endwhile()
set(APRG_DIR ${ABSOLUTE_CURRENT_DIR})

#Assign common flags, definitions and macros
include(${APRG_DIR}/AprgCMakeHelpers/CommonFlags.cmake)
include(${APRG_DIR}/AprgCMakeHelpers/CommonDefinitions.cmake)

#Add specific definitions
if(WIN32)
    #set for path of 7Zip for windows 32
    add_definitions(-DPATH_OF_7Z_EXECUTABLE="${APRG_DIR}AprgFileExtractor/7z32/7z.exe")
    add_definitions(-DPATH_OF_7Z_TEMP_FILE="${APRG_DIR}AprgFileExtractor/7z32/TempFile.txt")
endif()

#Include other projects
include(${APRG_DIR}/gtest/AprgCmakeInclude/gtest.cmake)
include(${APRG_DIR}/AprgCommon/AprgCmakeInclude/AprgCommon.cmake)
include(${APRG_DIR}/AprgAlgorithm/AprgCmakeInclude/AprgAlgorithm.cmake)
include(${APRG_DIR}/AprgFileExtractor/AprgCmakeInclude/AprgFileExtractor.cmake)
include(${APRG_DIR}/AprgGrepStringEvaluator/AprgCmakeInclude/AprgGrepStringEvaluator.cmake)

#Add files and directories
include(${QUICKEST_WAY_TO_PROGRAM_DIR}/cmake/FilesAndDirectories.cmake)

#Do final steps
add_executable(${OUTFILE} ${QUICKEST_WAY_TO_PROGRAM_SOURCES_AND_TESTS})
include_directories(${QUICKEST_WAY_TO_PROGRAM_INCLUDE_DIRECTORIES} ${QUICKEST_WAY_TO_PROGRAM_TEST_INCLUDE_DIRECTORIES} ${GTEST_INCLUDE_DIRS})
target_link_libraries(${OUTFILE} ${CMAKE_THREAD_LIBS_INIT} APRG_FILE_EXTRACTOR APRG_GREP_STRING_EVALUATOR APRG_ALGORITHM APRG_COMMON gtest ${CMAKE_THREAD_LIBS_INIT})
add_test(${OUTFILE} ${OUTFILE})
