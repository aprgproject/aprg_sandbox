cmake_minimum_required(VERSION 2.8)
project(TUPC_SAMPLE C CXX)

set(OUTFILE ${PROJECT_NAME})

#Assign CMake Directory
set(CMAKE_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR})

#Include macros to find directories and files
include(${CMAKE_DIRECTORY}/cmake/Macros.cmake)

#Assign all base directories to include
set(BASE_DIRECTORIES
    ${CMAKE_DIRECTORY}/../I_Interface
    ${CMAKE_DIRECTORY}/SS_TUPC
)

#Assign Flags
set(CMAKE_C_FLAGS "-Wall -Wextra -pedantic --coverage -std=c99")
set(CMAKE_CXX_FLAGS "-Wall -Wextra -pedantic --coverage -std=c++11")
if(WIN32)
    #add -mwindows for windows GUI, do not add for console build
    #set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -mwindows")
    #set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -mwindows")
endif()

#Assign Definitions
add_definitions(-DAPRG_DIR="${APRG_DIR}")

#Use MACRO_GET_SUBDIRECTORIES sub directories
MACRO_GET_SUBDIRECTORIES(SUB_DIRECTORIES BASE_DIRECTORIES)

#Use MACRO_GET_FILES to find files
MACRO_GET_FILES(SOURCE_FILES SUB_DIRECTORIES)

include_directories(SUB_DIRECTORIES)
add_executable(${OUTFILE} ${SOURCE_FILES})
