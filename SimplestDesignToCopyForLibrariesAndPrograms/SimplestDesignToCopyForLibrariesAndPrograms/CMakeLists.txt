cmake_minimum_required(VERSION 3.16)

#set project details
project(SimplestDesignToCopyForLibrariesAndPrograms C CXX)
set(OUTFILE ${PROJECT_NAME})
set(SIMPLEST_DESIGN_TO_COPY_FOR_LIBRARIES_AND_PROGRAMS_DIR ${CMAKE_CURRENT_SOURCE_DIR})

#Comment out TEST_MODE to build static executable, other cmakes check this
set(TEST_MODE "ON")

#Locate APRG Directory first because its used on other cmakes
include(${SIMPLEST_DESIGN_TO_COPY_FOR_LIBRARIES_AND_PROGRAMS_DIR}/cmake/LocateAprgDirectory.cmake)

#Assign common flags, definitions and macros
include(${APRG_DIR}/AprgCMakeHelpers/CommonFlags.cmake)include(${APRG_DIR}/AprgCMakeHelpers/CommonDefinitions.cmake)

#Include other projects
include(${APRG_DIR}/gtest/AprgCmakeInclude/gtest.cmake)include(${APRG_DIR}/AprgCommon/AprgCmakeInclude/AprgCommon.cmake)

#Add files and directories
include(${SIMPLEST_DESIGN_TO_COPY_FOR_LIBRARIES_AND_PROGRAMS_DIR}/cmake/FilesAndDirectories.cmake)

#Do final steps
if (TEST_MODE)
    set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} ${APRG_COMPILER_FLAGS_FOR_DEBUG}")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${APRG_COMPILER_FLAGS_FOR_DEBUG}")
    add_executable(${OUTFILE} ${SIMPLEST_DESIGN_TO_COPY_FOR_LIBRARIES_AND_PROGRAMS_SOURCES_AND_TESTS})
    include_directories(${SIMPLEST_DESIGN_TO_COPY_FOR_LIBRARIES_AND_PROGRAMS_INCLUDE_DIRECTORIES} ${SIMPLEST_DESIGN_TO_COPY_FOR_LIBRARIES_AND_PROGRAMS_TEST_INCLUDE_DIRECTORIES} ${GTEST_INCLUDE_DIRS})
    target_link_libraries(${OUTFILE} ${CMAKE_THREAD_LIBS_INIT} APRG_COMMON gtest ${CMAKE_THREAD_LIBS_INIT})
    add_test(${OUTFILE} ${OUTFILE})
else()
    set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} ${APRG_COMPILER_FLAGS_FOR_RELEASE_WITH_SPEED}")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${APRG_COMPILER_FLAGS_FOR_RELEASE_WITH_SPEED}")
    set(CMAKE_EXE_LINKER_FLAGS ${APRG_LINKER_FLAGS_FOR_RELEASE_WITH_STRIP})
    add_executable(${OUTFILE} ${SIMPLEST_DESIGN_TO_COPY_FOR_LIBRARIES_AND_PROGRAMS_SOURCES} ${SIMPLEST_DESIGN_TO_COPY_FOR_LIBRARIES_AND_PROGRAMS_MAIN_SOURCES})
    include_directories(${SIMPLEST_DESIGN_TO_COPY_FOR_LIBRARIES_AND_PROGRAMS_INCLUDE_DIRECTORIES})
    target_link_libraries(${OUTFILE} APRG_COMMON)
endif()
include(${APRG_DIR}/AprgCMakeHelpers/LastStep.cmake)