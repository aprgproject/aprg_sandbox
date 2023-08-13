cmake_minimum_required(VERSION 3.16)

#set project details
project(benchmark C CXX)
set(OUTFILE ${PROJECT_NAME})
set(BENCHMARK_DIR ${CMAKE_CURRENT_SOURCE_DIR})
set(BENCHMARK_FROM_GIT_HUB_DIR ${CMAKE_CURRENT_SOURCE_DIR}/../benchmarkFromGitHub/)

#Locate APRG Directory first because its used on other cmakes
include(${BENCHMARK_DIR}/cmake/LocateAprgDirectory.cmake)

#Assign macros, common flags, definitions and other common steps
include(${APRG_DIR}/AprgCMakeHelpers/AllCommonSteps.cmake)

#Include other projects
include(${APRG_DIR}/gtest/AprgCmakeInclude/gtest.cmake)include(${APRG_DIR}/AprgCommon/AprgCmakeInclude/AprgCommon.cmake)

#Add files and directories
include(${BENCHMARK_DIR}/cmake/FilesAndDirectories.cmake)
#Do final steps
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} ${APRG_COMPILER_FLAGS_FOR_RELEASE_WITH_SPEED}")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${APRG_COMPILER_FLAGS_FOR_RELEASE_WITH_SPEED}")
add_executable(${OUTFILE} ${BENCHMARK_SOURCES_AND_TESTS})
include_directories(${BENCHMARK_INCLUDE_DIRECTORIES} ${BENCHMARK_TEST_INCLUDE_DIRECTORIES} ${GTEST_INCLUDE_DIRS})
target_link_libraries(${OUTFILE} APRG_COMMON ${APRG_SHLWAPI_DEPENDENCIES} ${APRG_GTEST_DEPENDENCIES})
add_test(${OUTFILE} ${OUTFILE})
include(${APRG_DIR}/AprgCMakeHelpers/LastStep.cmake)