cmake_minimum_required(VERSION 3.16)
project(HeartTee C CXX)

#set project details
set(OUTFILE ${PROJECT_NAME})
set(HEART_TEE_DIR ${CMAKE_CURRENT_SOURCE_DIR})

#Comment out TEST_MODE to build static executable, other cmakes check this
set(TEST_MODE "ON")

#Locate APRG Directory first because its used on other cmakes
include(${HEART_TEE_DIR}/cmake/LocateAprgDirectory.cmake)

#Assign common flags, definitions and macros
include(${APRG_DIR}/AprgCMakeHelpers/CommonFlags.cmake)include(${APRG_DIR}/AprgCMakeHelpers/CommonDefinitions.cmake)

#Include other projects
include(${APRG_DIR}/gtest/AprgCmakeInclude/gtest.cmake)
#Add files and directories
include(${HEART_TEE_DIR}/cmake/FilesAndDirectories.cmake)

set(SPECIAL_INCLUDE_DIRECTORIES
    src/HeartTee
    src/SerialPort
    src/SqlConnect
    src/Fourier
)

#Do final steps
if (TEST_MODE)
    set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} ${APRG_COMPILER_FLAGS_FOR_DEBUG}")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${APRG_COMPILER_FLAGS_FOR_DEBUG}")
    add_executable(${OUTFILE} ${HEART_TEE_SOURCES_AND_TESTS})
    include_directories(${HEART_TEE_INCLUDE_DIRECTORIES} ${HEART_TEE_TEST_INCLUDE_DIRECTORIES} ${SPECIAL_INCLUDE_DIRECTORIES} ${GTEST_INCLUDE_DIRS})
    target_link_libraries(${OUTFILE} gtest ${CMAKE_THREAD_LIBS_INIT} mysqlclient)
    add_test(${OUTFILE} ${OUTFILE})
else()
    set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} ${APRG_COMPILER_FLAGS_FOR_RELEASE_WITH_SPEED}")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${APRG_COMPILER_FLAGS_FOR_RELEASE_WITH_SPEED}")
    set(CMAKE_EXE_LINKER_FLAGS ${APRG_LINKER_FLAGS_FOR_RELEASE_WITH_STRIP})
    add_executable(${OUTFILE} ${HEART_TEE_SOURCES} ${HEART_TEE_MAIN_SOURCES})
    include_directories(${HEART_TEE_INCLUDE_DIRECTORIES} ${SPECIAL_INCLUDE_DIRECTORIES})
    target_link_libraries(${OUTFILE} mysqlclient)
endif()
include(${APRG_DIR}/AprgCMakeHelpers/LastStep.cmake)