cmake_minimum_required(VERSION 2.8)
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
include(${BOOST_DIR}/cmake/IncludeBoost.cmake)

add_executable(${OUTFILE} ${BOOST_SOURCES_AND_TESTS})
include_directories(${BOOST_INCLUDE_DIRECTORIES} ${BOOST_TEST_INCLUDE_DIRECTORIES} ${GTEST_INCLUDE_DIRS})
target_link_libraries(${OUTFILE} ${CMAKE_THREAD_LIBS_INIT} APRG_COMMON gtest ${Boost_LIBRARIES} iconv)
add_test(${OUTFILE} ${OUTFILE})
