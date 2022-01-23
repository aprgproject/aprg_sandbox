cmake_minimum_required(VERSION 2.8)
project(AprgGnuPlot C CXX)

set(OUTFILE ${PROJECT_NAME})
#Comment out TEST_MODE to build static executable
set(TEST_MODE "ON")

#Assign APRG Directory
set(APRG_DIR ${CMAKE_CURRENT_SOURCE_DIR}/../../)
set(APRG_GNU_PLOT_DIR ${CMAKE_CURRENT_SOURCE_DIR})

#Assign Flags
include(${APRG_DIR}/AprgCMakeHelpers/CommonFlags.cmake)
#Assign Definitions
include(${APRG_DIR}/AprgCMakeHelpers/CommonDefinitions.cmake)

#Include gtest, this needs APRG Directory
include(${APRG_DIR}/gtest/AprgCmakeInclude/gtest.cmake)

#Include AprgCommon, this needs APRG Directory
include(${APRG_DIR}/AprgCommon/AprgCmakeInclude/AprgCommon.cmake)

#Include boost, this needs APRG Directory
include(${APRG_DIR}/Boost/AprgCmakeInclude/boost.cmake)

#Include AprgAlgebra, this needs APRG Directory
include(${APRG_DIR}/AprgAlgebra/AprgCmakeInclude/AprgAlgebra.cmake)

#Include AprgGeometry, this needs APRG Directory
include(${APRG_DIR}/AprgGeometry/AprgCmakeInclude/AprgGeometry.cmake)

#Add files and directories
include(${APRG_GNU_PLOT_DIR}/cmake/FilesAndDirectories.cmake)

add_executable(${OUTFILE} ${APRG_GNU_PLOT_SOURCES_AND_TESTS})
include_directories(${APRG_GNU_PLOT_INCLUDE_DIRECTORIES} ${APRG_GNU_PLOT_TEST_INCLUDE_DIRECTORIES} ${GTEST_INCLUDE_DIRS})
target_link_libraries(${OUTFILE} ${CMAKE_THREAD_LIBS_INIT} APRG_GEOMETRY APRG_ALGEBRA APRG_COMMON gtest ${Boost_LIBRARIES})
add_test(${OUTFILE} ${OUTFILE})