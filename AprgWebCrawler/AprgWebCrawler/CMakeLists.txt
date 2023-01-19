cmake_minimum_required(VERSION 3.16)

#set project details
project(AprgWebCrawler C CXX)
set(OUTFILE ${PROJECT_NAME})
set(APRG_WEB_CRAWLER_DIR ${CMAKE_CURRENT_SOURCE_DIR})

#Locate APRG Directory first because its used on other cmakes
include(${APRG_WEB_CRAWLER_DIR}/cmake/LocateAprgDirectory.cmake)

#Assign common flags, definitions and macros
include(${APRG_DIR}/AprgCMakeHelpers/CommonFlags.cmake)
include(${APRG_DIR}/AprgCMakeHelpers/CommonDefinitions.cmake)

#Assign specific definitions
add_definitions(-DAPRG_WEB_CRAWLER_CONFIGURATION_FILE="${APRG_DIR}AprgWebCrawler/Configuration/configuration.txt")
add_definitions(-DAPRG_WEB_CRAWLER_AUTOMATION_CONFIGURATION_FILE="${APRG_DIR}AprgWebCrawler/Configuration/firefoxConfiguration.txt")
add_definitions(-DAPRG_CRAWLER_TEST_DIRECTORY="${APRG_DIR}AprgWebCrawler/TestDirectory")
add_definitions(-DAPRG_CRAWLER_TEST_TEMPORARY_FILE_PATH="${APRG_DIR}AprgWebCrawler/TemporaryFile/temp.txt")
add_definitions(-DAPRG_WEB_CRAWLER_FIX_BATCH_FILE="${APRG_DIR}AprgWebCrawler/fixDirectoryNames.bat")

#Include other projects
include(${APRG_DIR}/AprgCommon/AprgCmakeInclude/AprgCommon.cmake)
include(${APRG_DIR}/CurlCpp/AprgCmakeInclude/CurlCpp.cmake)
include(${APRG_DIR}/AprgLocalUserAutomation/AprgCmakeInclude/AprgLocalUserAutomation.cmake)

#Add files and directories
include(${APRG_WEB_CRAWLER_DIR}/cmake/FilesAndDirectories.cmake)

set(INCLUDE_DIRECTORIES
    ${APRG_WEB_CRAWLER_INCLUDE_DIRECTORIES}
)

#Do final steps
set(CMAKE_C_FLAGS "${APRG_COMPILER_COMMON_FLAGS} ${APRG_COMPILER_FLAGS_FOR_RELEASE_WITH_SPEED}") # remove -std=c17
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${APRG_COMPILER_FLAGS_FOR_RELEASE_WITH_SPEED}")
set(CMAKE_EXE_LINKER_FLAGS ${APRG_LINKER_FLAGS_FOR_RELEASE_WITH_STRIP})
add_executable(${OUTFILE} ${APRG_WEB_CRAWLER_SOURCES})
include_directories(${APRG_WEB_CRAWLER_INCLUDE_DIRECTORIES} ${GTEST_INCLUDE_DIRS})
target_link_libraries(${OUTFILE} ${CMAKE_THREAD_LIBS_INIT} APRG_LOCAL_USER_AUTOMATION CURL_CPP APRG_COMMON)
include(${APRG_DIR}/AprgCMakeHelpers/LastStep.cmake)
