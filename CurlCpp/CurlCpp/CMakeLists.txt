cmake_minimum_required(VERSION 2.8)

# Setting up project
project(CurlCpp)

set(OUTFILE ${PROJECT_NAME})

#Assign APRG Directory
set(APRG_DIR ${CMAKE_CURRENT_SOURCE_DIR}/../../)
set(CURL_CPP_DIR ${APRG_DIR}/CurlCpp/CurlCpp/)

#Assign Flags
set(CMAKE_C_FLAGS "-Wall -Wextra -pedantic --coverage -std=c99 -mwindows")
set(CMAKE_CXX_FLAGS "-Wall -Wextra -pedantic --coverage -std=c++11 -mwindows")

# Add MacPorts
if(${CMAKE_SYSTEM_NAME} MATCHES "Darwin")
  set(CMAKE_PREFIX_PATH /opt/local ${CMAKE_PREFIX_PATH})
endif()

#Include aprgCommon, this needs APRG Directory
include(${APRG_DIR}/AprgCommon/AprgCmakeInclude/AprgCommon.cmake)

#Include curl library, this needs APRG Directory
include(${APRG_DIR}/curl-7.38.0/AprgCmakeInclude/curl.cmake)

#Include CURL_CPP_SOURCES
include(${CURL_CPP_DIR}/cmake/FilesAndDirectories.cmake)

set(CURL_CPP_TESTS
    tst/easy.cpp)

add_executable(${OUTFILE} ${CURL_CPP_SOURCES} ${CURL_CPP_TESTS})
include_directories(${CURL_CPP_INCLUDE_DIRECTORIES} ${GTEST_INCLUDE_DIRS})
target_link_libraries(${OUTFILE} APRG_COMMON CURL_LIB wsock32 ws2_32)
add_test(${OUTFILE} ${OUTFILE})