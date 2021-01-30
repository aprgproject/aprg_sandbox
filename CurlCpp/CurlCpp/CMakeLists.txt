cmake_minimum_required(VERSION 2.8)

# Setting up project
project(CurlCpp)

set(OUTFILE ${PROJECT_NAME})

#Assign APRG Directory
set(APRG_DIR ${CMAKE_CURRENT_SOURCE_DIR}/../../)
set(CURL_CPP_DIR ${CMAKE_CURRENT_SOURCE_DIR})

#Assign Flags
include(${APRG_DIR}/AprgCMakeHelpers/CommonFlags.cmake)

#Assign Definitions
include(${APRG_DIR}/AprgCMakeHelpers/CommonDefinitions.cmake)

# Add MacPorts
if(${CMAKE_SYSTEM_NAME} MATCHES "Darwin")  set(CMAKE_PREFIX_PATH /opt/local ${CMAKE_PREFIX_PATH})
endif()

#Include AprgCommon, this needs APRG Directoryinclude(${APRG_DIR}/AprgCommon/AprgCmakeInclude/AprgCommon.cmake)

#Include curl, this needs APRG Directory
include(${APRG_DIR}/curl-7.38.0/AprgCmakeInclude/curl.cmake)

#Include CURL_CPP_SOURCES
include(${CURL_CPP_DIR}/cmake/FilesAndDirectories.cmake)

set(CURL_CPP_TESTS
    tst/easy.cpp
)

add_executable(${OUTFILE} ${CURL_CPP_SOURCES} ${CURL_CPP_TESTS})
include_directories(${CURL_CPP_INCLUDE_DIRECTORIES} ${GTEST_INCLUDE_DIRS})
target_link_libraries(${OUTFILE} CURL_LIB wsock32 ws2_32 APRG_COMMON)
add_test(${OUTFILE} ${OUTFILE})
