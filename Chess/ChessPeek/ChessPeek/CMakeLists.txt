cmake_minimum_required(VERSION 3.16)

#set project details
project(ChessPeek C CXX)
set(OUTFILE ${PROJECT_NAME})
set(CHESS_PEEK_DIR ${CMAKE_CURRENT_SOURCE_DIR})

#Comment out TEST_MODE to build static executable, other cmakes check this
set(TEST_MODE "ON")

#Locate APRG Directory first because its used on other cmakes
include(${CHESS_PEEK_DIR}/cmake/LocateAprgDirectory.cmake)

#Assign macros, common flags, definitions and other common steps
include(${APRG_DIR}/AprgCMakeHelpers/AllCommonSteps.cmake)

#Include other projects
include(${APRG_DIR}/gtest/AprgCmakeInclude/gtest.cmake)
include(${APRG_DIR}/AprgCommon/AprgCmakeInclude/AprgCommon.cmake)
include(${APRG_DIR}/AprgLocalScreenMonitoring/AprgCmakeInclude/AprgLocalScreenMonitoring.cmake)
include(${APRG_DIR}/AprgBitmap/AprgCmakeInclude/AprgBitmap.cmake)
include(${APRG_DIR}/AprgLocalUserAutomation/AprgCmakeInclude/AprgLocalUserAutomation.cmake)
include(${APRG_DIR}/Chess/ChessUtilities/AprgCmakeInclude/ChessUtilities.cmake)

#Add files and directories
include(${CHESS_PEEK_DIR}/cmake/FilesAndDirectories.cmake)

#Do final steps
if (TEST_MODE)
    set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} ${APRG_COMPILER_FLAGS_FOR_DEBUG}")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${APRG_COMPILER_FLAGS_FOR_DEBUG}")
    add_executable(${OUTFILE} ${CHESS_PEEK_SOURCES_AND_TESTS})
    include_directories(${CHESS_PEEK_INCLUDE_DIRECTORIES} ${CHESS_PEEK_TEST_INCLUDE_DIRECTORIES} ${GTEST_INCLUDE_DIRS})
    target_link_libraries(${OUTFILE} CHESS_UTILITIES APRG_LOCAL_USER_AUTOMATION APRG_BITMAP APRG_LOCAL_SCREEN_MONITORING APRG_COMMON ${APRG_GTEST_DEPENDENCIES})
    add_test(${OUTFILE} ${OUTFILE})
else()
    set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} ${APRG_COMPILER_FLAGS_FOR_RELEASE_WITH_SPEED}")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${APRG_COMPILER_FLAGS_FOR_RELEASE_WITH_SPEED}")
    set(CMAKE_EXE_LINKER_FLAGS ${APRG_LINKER_FLAGS_FOR_RELEASE_WITH_STRIP})
    add_executable(${OUTFILE} ${CHESS_PEEK_SOURCES} ${CHESS_PEEK_MAIN_SOURCES})
    include_directories(${CHESS_PEEK_INCLUDE_DIRECTORIES})
    target_link_libraries(${OUTFILE} CHESS_UTILITIES APRG_LOCAL_USER_AUTOMATION APRG_BITMAP APRG_LOCAL_SCREEN_MONITORING APRG_COMMON)
endif()
include(${APRG_DIR}/AprgCMakeHelpers/LastStep.cmake)
