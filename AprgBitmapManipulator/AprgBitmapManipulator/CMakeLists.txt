cmake_minimum_required(VERSION 3.16)

#set project details
project(AprgBitmapManipulator C CXX)
set(OUTFILE ${PROJECT_NAME})
set(APRG_BITMAP_MANIPULATOR_DIR ${CMAKE_CURRENT_SOURCE_DIR})

#Locate APRG Directory first because its used on other cmakes
include(${APRG_BITMAP_MANIPULATOR_DIR}/cmake/LocateAprgDirectory.cmake)

#Assign macros, common flags, definitions and other common steps
include(${APRG_DIR}/AprgCMakeHelpers/AllCommonSteps.cmake)

#Include other projects
include(${APRG_DIR}/gtest/AprgCmakeInclude/gtest.cmake)include(${APRG_DIR}/AprgCommon/AprgCmakeInclude/AprgCommon.cmake)
include(${APRG_DIR}/AprgAlgorithm/AprgCmakeInclude/AprgAlgorithm.cmake)
include(${APRG_DIR}/AprgBitmap/AprgCmakeInclude/AprgBitmap.cmake)
include(${APRG_DIR}/AprgGeometry/AprgCmakeInclude/AprgGeometry.cmake)include(${APRG_DIR}/AprgStatistics/AprgCmakeInclude/AprgStatistics.cmake)

#Add files and directories
include(${APRG_BITMAP_MANIPULATOR_DIR}/cmake/FilesAndDirectories.cmake)

#Do final steps
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} ${APRG_COMPILER_FLAGS_FOR_DEBUG}")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${APRG_COMPILER_FLAGS_FOR_DEBUG}")
add_executable(${OUTFILE} ${APRG_BITMAP_MANIPULATOR_SOURCES_AND_TESTS})
include_directories(${APRG_BITMAP_MANIPULATOR_INCLUDE_DIRECTORIES} ${APRG_BITMAP_MANIPULATOR_TEST_INCLUDE_DIRECTORIES} ${GTEST_INCLUDE_DIRS})
target_link_libraries(${OUTFILE} APRG_STATISTICS APRG_GEOMETRY APRG_BITMAP APRG_COMMON ${APRG_GTEST_DEPENDENCIES})
add_test(${OUTFILE} ${OUTFILE})
include(${APRG_DIR}/AprgCMakeHelpers/LastStep.cmake)