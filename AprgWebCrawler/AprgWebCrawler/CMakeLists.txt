cmake_minimum_required(VERSION 2.8)
project(AprgWebCrawler C CXX)

set(OUTFILE ${PROJECT_NAME})

#Assign APRG Directory
set(APRG_DIR ${CMAKE_CURRENT_SOURCE_DIR}/../../)
set(APRG_WEB_CRAWLER_DIR ${APRG_DIR}/AprgWebCrawler/AprgWebCrawler/)

#Assign Flags do not include -mwindows to make a console build
set(CMAKE_C_FLAGS "-Wall -Wextra -pedantic --coverage -std=c99")
set(CMAKE_CXX_FLAGS "-Wall -Wextra -pedantic --coverage -std=c++11")
if(WIN32)
    #add -mwindows for windows GUI, do not add for console build
    #set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -mwindows")
    #set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -mwindows")
endif()

#Assign Definitions
add_definitions(-DAPRG_DIR="${APRG_DIR}")
add_definitions(-DAPRG_WEB_CRAWLER_CONFIGURATION_FILE="${APRG_DIR}AprgWebCrawler/Configuration/configuration.txt")
add_definitions(-DAPRG_WEB_CRAWLER_AUTOMATION_CONFIGURATION_FILE="${APRG_DIR}AprgWebCrawler/Configuration/firefoxConfiguration.txt")
add_definitions(-DAPRG_CRAWLER_TEST_DIRECTORY="${APRG_DIR}AprgWebCrawler/TestDirectory")
add_definitions(-DAPRG_CRAWLER_TEST_TEMPORARY_FILE_PATH="${APRG_DIR}AprgWebCrawler/TemporaryFile/temp.txt")
add_definitions(-DAPRG_WEB_CRAWLER_FIX_BATCH_FILE="${APRG_DIR}AprgWebCrawler/fixDirectoryNames.bat")

#Include AprgCommon, this needs APRG Directory
include(${APRG_DIR}/AprgCommon/AprgCmakeInclude/AprgCommon.cmake)

#Include CurlCpp, this needs APRG Directory
include(${APRG_DIR}/CurlCpp/AprgCmakeInclude/CurlCpp.cmake)

#Add files and directories
include(${APRG_WEB_CRAWLER_DIR}/cmake/FilesAndDirectories.cmake)

set(INCLUDE_DIRECTORIES
    ${APRG_WEB_CRAWLER_INCLUDE_DIRECTORIES}
)

set(CMAKE_FIND_LIBRARY_SUFFIXES ".a")
set(BUILD_SHARED_LIBRARIES OFF)
set(CMAKE_EXE_LINKER_FLAGS "-static")
add_executable(${OUTFILE} ${APRG_WEB_CRAWLER_SOURCES})
include_directories(${APRG_WEB_CRAWLER_INCLUDE_DIRECTORIES} ${GTEST_INCLUDE_DIRS})
target_link_libraries(${OUTFILE} ${CMAKE_THREAD_LIBS_INIT} CURL_CPP APRG_COMMON)
