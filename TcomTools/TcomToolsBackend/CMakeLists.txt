cmake_minimum_required(VERSION 2.8)
project(TcomToolsBackend C CXX)

set(OUTFILE ${PROJECT_NAME})

#Assign APRG Directory
set(APRG_DIR ${CMAKE_CURRENT_SOURCE_DIR}/../../)

#Assign Flags
set(CMAKE_C_FLAGS "-Wall -Wextra -pedantic --coverage -std=c99 -mwindows")
set(CMAKE_CXX_FLAGS "-Wall -Wextra -pedantic --coverage -std=c++11 -mwindows")

#Include gTest, this needs APRG Directory
include(${APRG_DIR}/gtest-1.7.0/AprgCmakeInclude/gtest.cmake)

#Include AprgCommon, this needs APRG Directory
include(${APRG_DIR}/AprgCommon/AprgCmakeInclude/AprgCommon.cmake)

set(SOURCES
    src/BtsLogPrint.cpp
    src/BtsLogPrint.hpp
    src/BtsLogSorter.cpp
    src/BtsLogSorter.hpp
    src/BtsLogSorterConfiguration.hpp
    src/BtsLogTime.cpp
    src/BtsLogTime.hpp
    src/BtsPrintReaderWithRollback.cpp
    src/BtsPrintReaderWithRollback.hpp
    tst/BtsLogPrint_unit.cpp
    tst/BtsLogSorter_unit.cpp
    tst/BtsLogTime_unit.cpp
)

add_executable(${OUTFILE} ${SOURCES})
include_directories(src ${GTEST_INCLUDE_DIRS})
target_link_libraries(${OUTFILE} gtest APRG_COMMON ${CMAKE_THREAD_LIBS_INIT})
add_test(${OUTFILE} ${OUTFILE})
