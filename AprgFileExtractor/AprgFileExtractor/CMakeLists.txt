cmake_minimum_required(VERSION 3.16)

#set project details
project(AprgFileExtractor C CXX)
set(OUTFILE ${PROJECT_NAME})
set(APRG_FILE_EXTRACTOR_DIR ${CMAKE_CURRENT_SOURCE_DIR})

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
if(WIN32)
    #set for path of 7Zip for windows 32
    add_definitions(-DPATH_OF_7Z_EXECUTABLE="${APRG_DIR}/AprgFileExtractor/7z32/7z.exe")
    add_definitions(-DPATH_OF_7Z_TEMP_FILE="${APRG_DIR}/AprgFileExtractor/7z32/TempFile.txt")
endif()

#Include other projects
include(${APRG_DIR}/gtest/AprgCmakeInclude/gtest.cmake)
include(${APRG_DIR}/AprgCommon/AprgCmakeInclude/AprgCommon.cmake)
include(${APRG_DIR}/AprgAlgorithm/AprgCmakeInclude/AprgAlgorithm.cmake)
include(${APRG_DIR}/AprgGrepStringEvaluator/AprgCmakeInclude/AprgGrepStringEvaluator.cmake)

#Add files and directories
include(${APRG_FILE_EXTRACTOR_DIR}/cmake/FilesAndDirectories.cmake)

#Comment out TEST_MODE to build static executable
set(TEST_MODE "ON")

#Do final steps
if (TEST_MODE)
    add_executable(${OUTFILE} ${APRG_FILE_EXTRACTOR_SOURCES_AND_TESTS})
    include_directories(${APRG_FILE_EXTRACTOR_INCLUDE_DIRECTORIES} ${APRG_FILE_EXTRACTOR_TEST_INCLUDE_DIRECTORIES} ${GTEST_INCLUDE_DIRS})
    target_link_libraries(${OUTFILE} gtest APRG_COMMON APRG_GREP_STRING_EVALUATOR ${CMAKE_THREAD_LIBS_INIT})
    add_test(${OUTFILE} ${OUTFILE})
else()
    set(CMAKE_FIND_LIBRARY_SUFFIXES ".a")
    set(BUILD_SHARED_LIBRARIES OFF)
    set(CMAKE_EXE_LINKER_FLAGS "-static")
    add_executable(${OUTFILE} ${APRG_FILE_EXTRACTOR_SOURCES} ${APRG_FILE_EXTRACTOR_MAIN_SOURCES})
    include_directories(${APRG_FILE_EXTRACTOR_INCLUDE_DIRECTORIES})
    target_link_libraries(${OUTFILE} APRG_COMMON APRG_GREP_STRING_EVALUATOR)
endif()

