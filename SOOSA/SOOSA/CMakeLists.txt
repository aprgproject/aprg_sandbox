cmake_minimum_required(VERSION 2.8)
project(SOOSA C CXX)

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

#Include aprgAlgorithm, this needs APRG Directory
include(${APRG_DIR}/AprgAlgorithm/AprgCmakeInclude/AprgAlgorithm.cmake)

#Include aprgBitmap, this needs APRG Directory
include(${APRG_DIR}/AprgBitmap/AprgCmakeInclude/AprgBitmap.cmake)

#Include gTest, this needs APRG Directory
include(${APRG_DIR}/gtest-1.7.0/AprgCmakeInclude/gtest.cmake)

set(SOURCES
    src/SOOSA.cpp
    src/SOOSA.hpp
    src/SoosaConfiguration.cpp
    src/SoosaConfiguration.hpp
    src/SoosaStatus.cpp
    src/SoosaStatus.hpp
    src/SoosaUi.cpp
    src/SoosaUi.hpp

)

set(MAIN_SOURCES
    src/main.cpp
)

set(TESTS
    tst/SOOSA_unit.cpp
)

set(INCLUDE_DIRECTORIES
    src/
)

if (TEST_MODE)
    add_executable(${OUTFILE} ${SOURCES} ${TESTS})
    include_directories(${INCLUDE_DIRECTORIES} ${GTEST_INCLUDE_DIRS})
    target_link_libraries(${OUTFILE} gtest APRG_COMMON APRG_BITMAP ${CMAKE_THREAD_LIBS_INIT})
    add_test(${OUTFILE} ${OUTFILE})
else()
    set(CMAKE_FIND_LIBRARY_SUFFIXES ".a")
    set(BUILD_SHARED_LIBRARIES OFF)
    set(CMAKE_EXE_LINKER_FLAGS "-static")
    add_executable(${OUTFILE} ${SOURCES} ${MAIN_SOURCES})
    include_directories(${INCLUDE_DIRECTORIES})
    target_link_libraries(${OUTFILE} APRG_COMMON APRG_BITMAP)
endif()
