cmake_minimum_required(VERSION 3.16)

#set project details
project(AprgUniqueProblems C CXX)
set(OUTFILE ${PROJECT_NAME})
set(APRG_UNIQUE_PROBLEMS_DIR ${CMAKE_CURRENT_SOURCE_DIR})

#Comment out TEST_MODE to build static executable, other cmakes check this
set(TEST_MODE "ON")

#Locate APRG Directory first because its used on other cmakes
include(${APRG_UNIQUE_PROBLEMS_DIR}/cmake/LocateAprgDirectory.cmake)

#Assign common flags, definitions and macros
include(${APRG_DIR}/AprgCMakeHelpers/CommonFlags.cmake)
include(${APRG_DIR}/AprgCMakeHelpers/CommonDefinitions.cmake)

#Include other projects
include(${APRG_DIR}/gtest/AprgCmakeInclude/gtest.cmake)
include(${APRG_DIR}/AprgCommon/AprgCmakeInclude/AprgCommon.cmake)
include(${APRG_DIR}/AprgAlgorithm/AprgCmakeInclude/AprgAlgorithm.cmake)

#Add Algorithm test files
include_directories(${APRG_ALGORITHM_TEST_INCLUDE_DIRECTORIES})

#Add files and directories
include(${APRG_UNIQUE_PROBLEMS_DIR}/cmake/FilesAndDirectories.cmake)

#Do final steps
if(TEST_MODE)
    set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} ${APRG_COMPILER_FLAGS_FOR_DEBUG}")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${APRG_COMPILER_FLAGS_FOR_DEBUG}")
    add_executable(${OUTFILE} ${APRG_UNIQUE_PROBLEMS_SOURCES_AND_TESTS})
    include_directories(${APRG_UNIQUE_PROBLEMS_INCLUDE_DIRECTORIES} ${APRG_UNIQUE_PROBLEMS_TEST_INCLUDE_DIRECTORIES} ${GTEST_INCLUDE_DIRS})
    target_link_libraries(${OUTFILE} ${CMAKE_THREAD_LIBS_INIT} APRG_COMMON gtest ${CMAKE_THREAD_LIBS_INIT} pthread)
    add_test(${OUTFILE} ${OUTFILE})
else()
    set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} ${APRG_COMPILER_FLAGS_FOR_RELEASE_WITH_SPEED}")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${APRG_COMPILER_FLAGS_FOR_RELEASE_WITH_SPEED}")
    set(CMAKE_EXE_LINKER_FLAGS ${APRG_LINKER_FLAGS_FOR_RELEASE_WITH_STRIP})
    add_executable(${OUTFILE} ${APRG_UNIQUE_PROBLEMS_SOURCES} ${APRG_UNIQUE_PROBLEMS_MAIN_SOURCES})
    include_directories(${APRG_UNIQUE_PROBLEMS_INCLUDE_DIRECTORIES})
    target_link_libraries(${OUTFILE} APRG_COMMON)
endif()
include(${APRG_DIR}/AprgCMakeHelpers/LastStep.cmake)
