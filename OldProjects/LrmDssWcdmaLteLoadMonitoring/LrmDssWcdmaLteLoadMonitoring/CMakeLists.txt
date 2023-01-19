cmake_minimum_required(VERSION 3.16)

#set project details
project(LrmDssWcdmaLteLoadMonitoring C CXX)
set(OUTFILE ${PROJECT_NAME})
set(LRM_DSS_WCDMA_LTE_LOAD_MONITORING_DIR ${CMAKE_CURRENT_SOURCE_DIR})

#Locate APRG Directory first because its used on other cmakes
include(${LRM_DSS_WCDMA_LTE_LOAD_MONITORING_DIR}/cmake/LocateAprgDirectory.cmake)

#Assign common flags, definitions and macros
include(${APRG_DIR}/AprgCMakeHelpers/CommonFlags.cmake)
include(${APRG_DIR}/AprgCMakeHelpers/CommonDefinitions.cmake)

#Include other projects
include(${APRG_DIR}/gtest/AprgCmakeInclude/gtest.cmake)
include(${APRG_DIR}/AprgCommon/AprgCmakeInclude/AprgCommon.cmake)

#Add files and directories
include(${LRM_DSS_WCDMA_LTE_LOAD_MONITORING_DIR}/cmake/FilesAndDirectories.cmake)

#Do final steps
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} ${APRG_COMPILER_FLAGS_FOR_DEBUG}")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${APRG_COMPILER_FLAGS_FOR_DEBUG}")
add_executable(${OUTFILE} ${LRM_DSS_WCDMA_LTE_LOAD_MONITORING_SOURCES_AND_TESTS})
include_directories(${LRM_DSS_WCDMA_LTE_LOAD_MONITORING_INCLUDE_DIRECTORIES} ${LRM_DSS_WCDMA_LTE_LOAD_MONITORING_TEST_INCLUDE_DIRECTORIES} ${GTEST_INCLUDE_DIRS})
target_link_libraries(${OUTFILE} ${CMAKE_THREAD_LIBS_INIT} APRG_COMMON gtest ${CMAKE_THREAD_LIBS_INIT})
add_test(${OUTFILE} ${OUTFILE})
include(${APRG_DIR}/AprgCMakeHelpers/LastStep.cmake)
