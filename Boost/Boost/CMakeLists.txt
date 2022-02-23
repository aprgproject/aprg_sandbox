cmake_minimum_required(VERSION 3.20)
project(BoostTest C CXX)

set(OUTFILE ${PROJECT_NAME})

#Comment out TEST_MODE to build static executable
set(TEST_MODE "ON")

#Assign APRG Directory
set(APRG_DIR ${CMAKE_CURRENT_SOURCE_DIR}/../../)
set(BOOST_DIR ${CMAKE_CURRENT_SOURCE_DIR})

#Assign Flags
include(${APRG_DIR}/AprgCMakeHelpers/CommonFlags.cmake)

#Assign Definitions
include(${APRG_DIR}/AprgCMakeHelpers/CommonDefinitions.cmake)

#Include gtest, this needs APRG Directory
include(${APRG_DIR}/gtest/AprgCmakeInclude/gtest.cmake)

#Include AprgCommon, this needs APRG Directory
include(${APRG_DIR}/AprgCommon/AprgCmakeInclude/AprgCommon.cmake)

include(${BOOST_DIR}/cmake/FilesAndDirectories.cmake)

add_executable(${OUTFILE} ${BOOST_TESTS})
include_directories(${BOOST_INCLUDE_DIRECTORIES} ${BOOST_TEST_INCLUDE_DIRECTORIES} ${GTEST_INCLUDE_DIRS})
if(WIN32)
    set(IconvLibraryIfNeeded "iconv")
endif()
target_link_libraries(${OUTFILE} ${Boost_LIBRARIES} APRG_COMMON gtest ${CMAKE_THREAD_LIBS_INIT} ${IconvLibraryIfNeeded})
add_test(${OUTFILE} ${OUTFILE})
