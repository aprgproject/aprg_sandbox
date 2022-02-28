cmake_minimum_required(VERSION 3.16)

#set project details
project(BoostTest C CXX)
set(OUTFILE ${PROJECT_NAME})
set(BOOST_DIR ${CMAKE_CURRENT_SOURCE_DIR})

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
include(${BOOST_DIR}/cmake/FilesAndDirectories.cmake)

#Do final steps
add_executable(${OUTFILE} ${BOOST_TESTS})
include_directories(${BOOST_INCLUDE_DIRECTORIES} ${BOOST_TEST_INCLUDE_DIRECTORIES} ${GTEST_INCLUDE_DIRS})
if(WIN32)
    set(IconvLibraryIfNeeded "iconv")
endif()
target_link_libraries(${OUTFILE} ${Boost_LIBRARIES} APRG_COMMON gtest ${CMAKE_THREAD_LIBS_INIT} ${IconvLibraryIfNeeded})
add_test(${OUTFILE} ${OUTFILE})
