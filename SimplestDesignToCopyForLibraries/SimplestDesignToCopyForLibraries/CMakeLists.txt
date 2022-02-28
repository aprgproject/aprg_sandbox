cmake_minimum_required(VERSION 3.16)

#set project details
project(SimplestDesignToCopyForLibraries C CXX)
set(OUTFILE ${PROJECT_NAME})
set(SIMPLEST_DESIGN_TO_COPY_FOR_LIBRARIES_DIR ${CMAKE_CURRENT_SOURCE_DIR})

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

#Add files and directories
include(${SIMPLEST_DESIGN_TO_COPY_FOR_LIBRARIES_DIR}/cmake/FilesAndDirectories.cmake)

#Do final steps
add_executable(${OUTFILE} ${SIMPLEST_DESIGN_TO_COPY_FOR_LIBRARIES_SOURCES_AND_TESTS})
include_directories(${SIMPLEST_DESIGN_TO_COPY_FOR_LIBRARIES_INCLUDE_DIRECTORIES} ${SIMPLEST_DESIGN_TO_COPY_FOR_LIBRARIES_TEST_INCLUDE_DIRECTORIES} ${GTEST_INCLUDE_DIRS})
target_link_libraries(${OUTFILE} ${CMAKE_THREAD_LIBS_INIT} APRG_COMMON gtest ${CMAKE_THREAD_LIBS_INIT})
add_test(${OUTFILE} ${OUTFILE})
