cmake_minimum_required(VERSION 3.16)
project(HeartTee C CXX)

#Comment out TEST_MODE to build static executable
set(TEST_MODE "ON")

#set project details
set(OUTFILE ${PROJECT_NAME})
set(HEART_TEE_DIR ${CMAKE_CURRENT_SOURCE_DIR})

#Locate APRG Directory first because its used on other cmakes
set(APRG_DIR ${CMAKE_CURRENT_SOURCE_DIR})
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

#Add files and directories
include(${HEART_TEE_DIR}/cmake/FilesAndDirectories.cmake)

set(SPECIAL_INCLUDE_DIRECTORIES
    src/HeartTee
    src/SerialPort
    src/SqlConnect
    src/Fourier
)

#Do final steps
if (TEST_MODE)
    add_executable(${OUTFILE} ${HEART_TEE_SOURCES_AND_TESTS})
    include_directories(${HEART_TEE_INCLUDE_DIRECTORIES} ${HEART_TEE_TEST_INCLUDE_DIRECTORIES} ${SPECIAL_INCLUDE_DIRECTORIES} ${GTEST_INCLUDE_DIRS})
    target_link_libraries(${OUTFILE} gtest ${CMAKE_THREAD_LIBS_INIT} mysqlclient)
    add_test(${OUTFILE} ${OUTFILE})
else()
    set(CMAKE_FIND_LIBRARY_SUFFIXES ".a")
    set(BUILD_SHARED_LIBRARIES OFF)
    #set(CMAKE_EXE_LINKER_FLAGS "-static")
    add_executable(${OUTFILE} ${HEART_TEE_SOURCES} ${HEART_TEE_MAIN_SOURCES})
    include_directories(${HEART_TEE_INCLUDE_DIRECTORIES} ${SPECIAL_INCLUDE_DIRECTORIES})
    target_link_libraries(${OUTFILE} mysqlclient)
endif()
