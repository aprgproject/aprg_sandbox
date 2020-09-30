cmake_minimum_required(VERSION 2.8)
project(AprgCommon C CXX)

set(OUTFILE ${PROJECT_NAME})

#Assign APRG Directory
set(APRG_DIR ${CMAKE_CURRENT_SOURCE_DIR}/../../)
set(APRG_COMMON_DIR ${APRG_DIR}/AprgCommon/AprgCommon/)

#Assign Flags
set(CMAKE_C_FLAGS "-Wall -Wextra -pedantic --coverage -std=c99 -mwindows")
set(CMAKE_CXX_FLAGS "-Wall -Wextra -pedantic --coverage -std=c++11 -mwindows")

#Include gTest, this needs APRG Directory
include(${APRG_DIR}/gtest-1.7.0/AprgCmakeInclude/gtest.cmake)

#Include APRG_COMMON_SOURCES
include(${APRG_COMMON_DIR}/cmake/AprgCommonSources.cmake)

set(SOURCES
    ${APRG_COMMON_SOURCES}
    tst/AlbaFileReader_unit.cpp
    tst/AlbaLargeSorter_unit.cpp
    tst/AlbaMacroArgumentCounter_unit.cpp
    tst/AlbaOptional_unit.cpp
    tst/AlbaPathHandler_unit.cpp
    tst/AlbaRaiiafPointer_unit.cpp
    tst/AlbaStringHelper_unit.cpp
    tst/AlbaWindowsTimer_unit.cpp
    tst/GrepStringEvaluator/AlbaGrepStringEvaluator_unit.cpp
)

add_executable(${OUTFILE} ${SOURCES})
include_directories(src ${GTEST_INCLUDE_DIRS})
target_link_libraries(${OUTFILE} gtest ${CMAKE_THREAD_LIBS_INIT})
add_test(${OUTFILE} ${OUTFILE})
