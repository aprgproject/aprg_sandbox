cmake_minimum_required(VERSION 3.16)

#set project details
project(CurlCpp)
set(OUTFILE ${PROJECT_NAME})
set(CURL_CPP_DIR ${CMAKE_CURRENT_SOURCE_DIR})

#Locate APRG Directory first because its used on other cmakes
include(${CURL_CPP_DIR}/cmake/LocateAprgDirectory.cmake)

#Assign common flags, definitions and macros
include(${APRG_DIR}/AprgCMakeHelpers/CommonFlags.cmake)include(${APRG_DIR}/AprgCMakeHelpers/CommonDefinitions.cmake)

# Add MacPorts
if(${CMAKE_SYSTEM_NAME} MATCHES "Darwin")  set(CMAKE_PREFIX_PATH /opt/local ${CMAKE_PREFIX_PATH})
endif()

#Include other projects
include(${APRG_DIR}/AprgCommon/AprgCmakeInclude/AprgCommon.cmake)
include(${APRG_DIR}/curl-7.38.0/AprgCmakeInclude/curl.cmake)

#Add files and directories
include(${CURL_CPP_DIR}/cmake/FilesAndDirectories.cmake)

set(CURL_CPP_TESTS
    tst/easy.cpp
)

#Do final steps
set(CMAKE_C_FLAGS "${APRG_COMPILER_COMMON_FLAGS} ${APRG_COMPILER_FLAGS_FOR_DEBUG}") # no -std=c17
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${APRG_COMPILER_FLAGS_FOR_DEBUG}")
add_executable(${OUTFILE} ${CURL_CPP_SOURCES} ${CURL_CPP_TESTS})
include_directories(${CURL_CPP_INCLUDE_DIRECTORIES} ${GTEST_INCLUDE_DIRS})
target_link_libraries(${OUTFILE} CURL_LIB wsock32 ws2_32 APRG_COMMON)
add_test(${OUTFILE} ${OUTFILE})
include(${APRG_DIR}/AprgCMakeHelpers/LastStep.cmake)