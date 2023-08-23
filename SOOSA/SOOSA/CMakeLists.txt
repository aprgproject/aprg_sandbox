cmake_minimum_required(VERSION 3.16)

#set project details
project(SOOSA C CXX)
set(OUTFILE ${PROJECT_NAME})
set(SOOSA_DIR ${CMAKE_CURRENT_SOURCE_DIR})

#Comment out TEST_MODE to build static executable, other cmakes check this
set(TEST_MODE "ON")

#Locate APRG Directory first because its used on other cmakes
include(${SOOSA_DIR}/cmake/LocateAprgDirectory.cmake)

#Assign macros, common flags, definitions and other common steps
include(${APRG_DIR}/AprgCMakeHelpers/AllCommonSteps.cmake)

#Include other projects
include(${APRG_DIR}/gtest/AprgCmakeInclude/gtest.cmake)
include(${APRG_DIR}/AprgCommon/AprgCmakeInclude/AprgCommon.cmake)
include(${APRG_DIR}/AprgStatistics/AprgCmakeInclude/AprgStatistics.cmake)
include(${APRG_DIR}/AprgGeometry/AprgCmakeInclude/AprgGeometry.cmake)
include(${APRG_DIR}/AprgBitmap/AprgCmakeInclude/AprgBitmap.cmake)

#Add files and directories
include(${SOOSA_DIR}/cmake/FilesAndDirectories.cmake)

#Do final steps
if(TEST_MODE)
    set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} ${APRG_COMPILER_FLAGS_FOR_DEBUG}")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${APRG_COMPILER_FLAGS_FOR_DEBUG}")
    add_executable(${OUTFILE} ${SOOSA_SOURCES_AND_TESTS})
    include_directories(${SOOSA_INCLUDE_DIRECTORIES} ${SOOSA_TEST_INCLUDE_DIRECTORIES} ${GTEST_INCLUDE_DIRS})
    target_link_libraries(${OUTFILE} APRG_BITMAP APRG_GEOMETRY APRG_STATISTICS APRG_COMMON ${APRG_GTEST_DEPENDENCIES})
    add_test(${OUTFILE} ${OUTFILE})
else()
    set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} ${APRG_COMPILER_FLAGS_FOR_RELEASE_WITH_SPEED}")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${APRG_COMPILER_FLAGS_FOR_RELEASE_WITH_SPEED}")
    set(CMAKE_EXE_LINKER_FLAGS ${APRG_LINKER_FLAGS_FOR_RELEASE_WITH_STRIP})
    add_executable(${OUTFILE} ${SOOSA_SOURCES} ${SOOSA_MAIN_SOURCES})
    include_directories(${SOOSA_INCLUDE_DIRECTORIES})
    target_link_libraries(${OUTFILE} APRG_BITMAP APRG_GEOMETRY APRG_STATISTICS APRG_COMMON)
endif()
include(${APRG_DIR}/AprgCMakeHelpers/LastStep.cmake)
