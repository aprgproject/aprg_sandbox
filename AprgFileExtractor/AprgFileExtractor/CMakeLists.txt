cmake_minimum_required(VERSION 2.8)
project(AprgFileExtractor C CXX)

set(OUTFILE ${PROJECT_NAME})

#Comment out TEST_MODE to build static executable
set(TEST_MODE "ON")

#Assign APRG Directory
set(APRG_DIR ${CMAKE_CURRENT_SOURCE_DIR}/../../)
set(APRG_FILE_EXTRACTOR_DIR ${APRG_DIR}/AprgFileExtractor/AprgFileExtractor/)

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
if(WIN32)
    #set for path of 7Zip for windows 32
    add_definitions(-DPATH_OF_7Z_EXECUTABLE="${APRG_DIR}AprgFileExtractor/7z32/7z.exe")
    add_definitions(-DPATH_OF_7Z_TEMP_FILE="${APRG_DIR}AprgFileExtractor/7z32/TempFile.txt")
endif()

#Include gTest, this needs APRG Directory
include(${APRG_DIR}/gtest-1.7.0/AprgCmakeInclude/gtest.cmake)

#Include AprgCommon, this needs APRG Directory
include(${APRG_DIR}/AprgCommon/AprgCmakeInclude/AprgCommon.cmake)

#Include AprgAlgorithm, this needs APRG Directory
include(${APRG_DIR}/AprgAlgorithm/AprgCmakeInclude/AprgAlgorithm.cmake)

#Add files and directories
include(${APRG_FILE_EXTRACTOR_DIR}/cmake/FilesAndDirectories.cmake)

set(MAIN_SOURCES
    ${APRG_FILE_EXTRACTOR_DIR}/src/main.cpp
)

if (TEST_MODE)
    add_executable(${OUTFILE} ${APRG_FILE_EXTRACTOR_SOURCES_AND_TESTS})
    include_directories(${APRG_FILE_EXTRACTOR_INCLUDE_DIRECTORIES} ${APRG_FILE_EXTRACTOR_TEST_INCLUDE_DIRECTORIES} ${GTEST_INCLUDE_DIRS})
    target_link_libraries(${OUTFILE} gtest APRG_COMMON APRG_ALGORITHM ${CMAKE_THREAD_LIBS_INIT})
    add_test(${OUTFILE} ${OUTFILE})
else()
    set(CMAKE_FIND_LIBRARY_SUFFIXES ".a")
    set(BUILD_SHARED_LIBRARIES OFF)
    set(CMAKE_EXE_LINKER_FLAGS "-static")
    add_executable(${OUTFILE} ${APRG_FILE_EXTRACTOR_SOURCES} ${MAIN_SOURCES})
    include_directories(${APRG_FILE_EXTRACTOR_INCLUDE_DIRECTORIES})
    target_link_libraries(${OUTFILE} APRG_COMMON APRG_ALGORITHM)
endif()

