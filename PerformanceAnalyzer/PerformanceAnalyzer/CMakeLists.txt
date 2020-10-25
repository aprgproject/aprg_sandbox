cmake_minimum_required(VERSION 2.8)
project(PerformanceAnalyzer C CXX)

set(OUTFILE ${PROJECT_NAME})

#Comment out TEST_MODE to build static executable
set(TEST_MODE "ON")

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

#Include aprgCommon, this needs APRG Directory
include(${APRG_DIR}/AprgCommon/AprgCmakeInclude/AprgCommon.cmake)

#Include AprgAlgorithm, this needs APRG Directory
include(${APRG_DIR}/AprgAlgorithm/AprgCmakeInclude/AprgAlgorithm.cmake)

#Include gTest, this needs APRG Directory
include(${APRG_DIR}/gtest-1.7.0/AprgCmakeInclude/gtest.cmake)

#Include AprgFileExtractor, this needs APRG Directory
include(${APRG_DIR}/AprgFileExtractor/AprgCmakeInclude/AprgFileExtractor.cmake)

#Include TcomToolsBackend, this needs APRG Directory
include(${APRG_DIR}/TcomTools/AprgCmakeInclude/TcomToolsBackend.cmake)


set(SOURCES
    src/PerformanceAnalyzer.cpp
    src/PerformanceAnalyzer.hpp
)

set(MAIN_SOURCES
    src/main.cpp
)

set(TESTS
    tst/PerformanceAnalyzer_unit.cpp
)

set(INCLUDE_DIRECTORIES
    src/
)

if (TEST_MODE)
    add_executable(${OUTFILE} ${SOURCES} ${TESTS})
    include_directories(${INCLUDE_DIRECTORIES} ${GTEST_INCLUDE_DIRS})
    target_link_libraries(APRG_FILE_EXTRACTOR APRG_COMMON APRG_ALGORITHM)
    target_link_libraries(${OUTFILE} ${CMAKE_THREAD_LIBS_INIT} gtest APRG_COMMON APRG_ALGORITHM APRG_FILE_EXTRACTOR TCOM_TOOLS_BACKEND)
    add_test(${OUTFILE} ${OUTFILE})
else()
    set(CMAKE_FIND_LIBRARY_SUFFIXES ".a")
    set(BUILD_SHARED_LIBRARIES OFF)
    set(CMAKE_EXE_LINKER_FLAGS "-static")
    add_executable(${OUTFILE} ${SOURCES} ${MAIN_SOURCES})
    include_directories(${INCLUDE_DIRECTORIES})
    target_link_libraries(${OUTFILE} APRG_COMMON APRG_ALGORITHM APRG_FILE_EXTRACTOR TCOM_TOOLS_BACKEND)
endif()
