cmake_minimum_required(VERSION 3.16)

#set project details
project(ChessEngineHandler C CXX)
set(OUTFILE ${PROJECT_NAME})
set(CHESS_ENGINE_HANDLER_DIR ${CMAKE_CURRENT_SOURCE_DIR})

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
include(${CHESS_ENGINE_HANDLER_DIR}/cmake/FilesAndDirectories.cmake)

#Comment out TEST_MODE to build static executable
#set(TEST_MODE "ON")

#Do final steps
if (TEST_MODE)    add_executable(${OUTFILE} ${CHESS_ENGINE_HANDLER_SOURCES_AND_TESTS})
    include_directories(${CHESS_ENGINE_HANDLER_INCLUDE_DIRECTORIES} ${CHESS_ENGINE_HANDLER_TEST_INCLUDE_DIRECTORIES} ${GTEST_INCLUDE_DIRS})
    target_link_libraries(${OUTFILE} ${CMAKE_THREAD_LIBS_INIT} APRG_COMMON gtest ${CMAKE_THREAD_LIBS_INIT})
    add_test(${OUTFILE} ${OUTFILE})else()
    set(CMAKE_FIND_LIBRARY_SUFFIXES ".a")
    set(BUILD_SHARED_LIBRARIES OFF)
    set(CMAKE_EXE_LINKER_FLAGS "-static")
    add_executable(${OUTFILE} ${CHESS_ENGINE_HANDLER_SOURCES} ${CHESS_ENGINE_HANDLER_MAIN_SOURCES})
    include_directories(${CHESS_ENGINE_HANDLER_INCLUDE_DIRECTORIES})
    target_link_libraries(${OUTFILE} APRG_COMMON)
endif()
