cmake_minimum_required(VERSION 3.16)

#set project details
project(AprgGnuPlot C CXX)
set(OUTFILE ${PROJECT_NAME})
set(APRG_GNU_PLOT_DIR ${CMAKE_CURRENT_SOURCE_DIR})

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
include(${APRG_DIR}/Boost/AprgCmakeInclude/boost.cmake)
include(${APRG_DIR}/AprgAlgebra/AprgCmakeInclude/AprgAlgebra.cmake)
include(${APRG_DIR}/AprgGeometry/AprgCmakeInclude/AprgGeometry.cmake)

#Add files and directories
include(${APRG_GNU_PLOT_DIR}/cmake/FilesAndDirectories.cmake)

#Do final steps
add_executable(${OUTFILE} ${APRG_GNU_PLOT_SOURCES_AND_TESTS})
include_directories(${APRG_GNU_PLOT_INCLUDE_DIRECTORIES} ${APRG_GNU_PLOT_TEST_INCLUDE_DIRECTORIES} ${GTEST_INCLUDE_DIRS})
target_link_libraries(${OUTFILE} APRG_GEOMETRY APRG_ALGEBRA APRG_COMMON gtest ${Boost_LIBRARIES}  ${CMAKE_THREAD_LIBS_INIT})
add_test(${OUTFILE} ${OUTFILE})
