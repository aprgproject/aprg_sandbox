cmake_minimum_required(VERSION 3.16)

#set project details
project(PidSimulator C CXX)
set(OUTFILE ${PROJECT_NAME})
set(PID_SIMULATOR_DIR ${CMAKE_CURRENT_SOURCE_DIR})

#Comment out TEST_MODE to build static executable, other cmakes check this
set(TEST_MODE "ON")

#Locate APRG Directory first because its used on other cmakes
get_filename_component(ABSOLUTE_CURRENT_DIR "${CMAKE_CURRENT_LIST_DIR}" ABSOLUTE)
get_filename_component(CURRENT_DIR_NAME "$${ABSOLUTE_CURRENT_DIR}" NAME)
while(NOT ${CURRENT_DIR_NAME} MATCHES "APRG")
    get_filename_component(ABSOLUTE_CURRENT_DIR "${ABSOLUTE_CURRENT_DIR}/.." ABSOLUTE)
    get_filename_component(CURRENT_DIR_NAME "$${ABSOLUTE_CURRENT_DIR}" NAME)
endwhile()
set(APRG_DIR ${ABSOLUTE_CURRENT_DIR})

#Assign common flags, definitions and macros
include(${APRG_DIR}/AprgCMakeHelpers/CommonFlags.cmake)
include(${APRG_DIR}/AprgCMakeHelpers/CommonDefinitions.cmake)

#Include other projects
include(${APRG_DIR}/gtest/AprgCmakeInclude/gtest.cmake)
include(${APRG_DIR}/AprgCommon/AprgCmakeInclude/AprgCommon.cmake)
include(${APRG_DIR}/AprgBitmap/AprgCmakeInclude/AprgBitmap.cmake)
include(${APRG_DIR}/AprgGeometry/AprgCmakeInclude/AprgGeometry.cmake)
include(${APRG_DIR}/AprgAlgebra/AprgCmakeInclude/AprgAlgebra.cmake)
include(${APRG_DIR}/AprgGraph/AprgCmakeInclude/AprgGraph.cmake)

#Add files and directories
include(${PID_SIMULATOR_DIR}/cmake/FilesAndDirectories.cmake)

#Do final steps
if (TEST_MODE)
    add_executable(${OUTFILE} ${PID_SIMULATOR_SOURCES_AND_TESTS})
    include_directories(${PID_SIMULATOR_INCLUDE_DIRECTORIES} ${PID_SIMULATOR_TEST_INCLUDE_DIRECTORIES} ${GTEST_INCLUDE_DIRS})
    target_link_libraries(${OUTFILE} gtest APRG_GRAPH APRG_ALGEBRA APRG_GEOMETRY APRG_BITMAP APRG_COMMON ${CMAKE_THREAD_LIBS_INIT})  # add real time library
    add_test(${OUTFILE} ${OUTFILE})
else()
    set(CMAKE_FIND_LIBRARY_SUFFIXES ".a")
    set(BUILD_SHARED_LIBRARIES OFF)
    set(CMAKE_EXE_LINKER_FLAGS "-static")
    add_executable(${OUTFILE} ${PID_SIMULATOR_SOURCES} ${PID_SIMULATOR_MAIN_SOURCES})
    include_directories(${PID_SIMULATOR_INCLUDE_DIRECTORIES})
    target_link_libraries(${OUTFILE} gtest APRG_GRAPH APRG_ALGEBRA APRG_GEOMETRY APRG_BITMAP APRG_COMMON) # add real time library
endif()
