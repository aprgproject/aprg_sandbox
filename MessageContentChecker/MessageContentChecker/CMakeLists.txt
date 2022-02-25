cmake_minimum_required(VERSION 3.16)
project(MessageContentChecker C CXX)

set(OUTFILE ${PROJECT_NAME})
#Comment out TEST_MODE to build static executable
set(TEST_MODE "ON")
#Assign APRG Directory
set(APRG_DIR ${CMAKE_CURRENT_SOURCE_DIR}/../../)
set(MESSAGE_CONTENT_CHECKER_DIR ${CMAKE_CURRENT_SOURCE_DIR})

#Assign Flags
include(${APRG_DIR}/AprgCMakeHelpers/CommonFlags.cmake)

#Assign Definitions
include(${APRG_DIR}/AprgCMakeHelpers/CommonDefinitions.cmake)

#Include gtest, this needs APRG Directory
include(${APRG_DIR}/gtest/AprgCmakeInclude/gtest.cmake)

#Include AprgCommon, this needs APRG Directory
include(${APRG_DIR}/AprgCommon/AprgCmakeInclude/AprgCommon.cmake)

#Add files and directories
include(${MESSAGE_CONTENT_CHECKER_DIR}/cmake/FilesAndDirectories.cmake)

#Assign Sack Directory
set(SackDirectory "D:/Branches/TCOM_WBTS17_0000")

set(SACKS_DIR_TO_INCLUDE
    ${SackDirectory}/I_Interface/Private/SC_TCOM/Temp
    ${SackDirectory}/wbts_integration/I_Interface/Global_Env/Definitions
    ${SackDirectory}/wbts_integration/I_Interface/Global_Env/Messages
    ${SackDirectory}/wbts_integration/I_Interface/Application_Env
    ${SackDirectory}/wbts_integration/I_Interface/Application_Env/Wn_Env/Bs_Env
    ${SackDirectory}/wbts_integration/I_Interface/Application_Env/Definitions
    ${SackDirectory}/wbts_integration/I_Interface/Application_Env/Wn_Env/Bs_Env/Definitions
    ${SackDirectory}/wbts_integration/I_Interface/Application_Env/Messages
    ${SackDirectory}/wbts_integration/I_Interface/Application_Env/Interfaces
    ${SackDirectory}/wbts_integration/I_Interface/Application_Env/Wn_Env/Bs_Env/Messages
    ${SackDirectory}/wbts_integration/I_Interface/Application_Env/Wn_Env/Bs_Env/Ppc_Env/Definitions
    ${SackDirectory}/wbts_integration/I_Interface/Application_Env/Wn_Env/Bs_Env/Ppc_Env/Messages
    ${SackDirectory}/wbts_integration/I_Interface/Application_Env/Wn_Env/Bs_Env/Dsp_Env/Definitions
    ${SackDirectory}/wbts_integration/I_Interface/Application_Env/Wn_Env/Bs_Env/Dsp_Env/Messages
    ${SackDirectory}/I_Interface/Private/SC_TCOM/Definitions
    ${SackDirectory}/I_Interface/Private/SC_TCOM/Messages
    ${SackDirectory}/wbts_integration/I_Interface/Platform_Env/CCS_ENV/MCU/Definitions
    ${SackDirectory}/wbts_integration/I_Interface/Platform_Env/CCS_ENV/MCU/Messages
    ${SackDirectory}/wbts_integration/I_Interface/Platform_Env/CCS_ENV/MCU/ServiceInterface
    ${SackDirectory}/wbts_integration/I_Interface/Platform_Env/CCS_ENV/COMMON/Definitions
    ${SackDirectory}/wbts_integration/I_Interface/Platform_Env/CCS_ENV/COMMON/Messages
    ${SackDirectory}/wbts_integration/I_Interface/Platform_Env/CCS_ENV/COMMON/ServiceInterface
    ${SackDirectory}/wbts_integration/I_Interface/Platform_Env/CCS_ENV/DSP/Definitions
    ${SackDirectory}/wbts_integration/I_Interface/Platform_Env/Messages
    ${SackDirectory}/wbts_integration/I_Interface/Platform_Env/MCUHWAPI_ENV/Definitions
    ${SackDirectory}/wbts_integration/I_Interface/Platform_Env/MCUHWAPI_ENV/Messages
    ${SackDirectory}/wbts_integration/I_Interface/Platform_Env/DSPHWAPI_ENV/Definitions
    ${SackDirectory}/wbts_integration/I_Interface/Platform_Env/DSPHWAPI_ENV/Messages
    ${SackDirectory}/wbts_integration/I_Interface/Platform_Env/UPHWAPI_ENV/DSP_AND_RTHWAPI_ENV/COMMON_ENV/Definitions
    ${SackDirectory}/wbts_integration/I_Interface/Platform_Env/UPHWAPI_ENV/DSP_AND_RTHWAPI_ENV/COMMON_ENV/Messages
    ${SackDirectory}/wbts_integration/I_Interface/Platform_Env/UPHWAPI_ENV/DSPHWAPI_ENV/FARADAY_ENV/Definitions
    ${SackDirectory}/wbts_integration/I_Interface/Platform_Env/Definitions
)

if (TEST_MODE)
    add_executable(${OUTFILE} ${MESSAGE_CONTENT_CHECKER_SOURCES_AND_TESTS})
    include_directories(${MESSAGE_CONTENT_CHECKER_INCLUDE_DIRECTORIES} ${MESSAGE_CONTENT_CHECKER_TEST_INCLUDE_DIRECTORIES} ${GTEST_INCLUDE_DIRS} ${SACKS_DIR_TO_INCLUDE})
    target_link_libraries(${OUTFILE} ${CMAKE_THREAD_LIBS_INIT} APRG_COMMON gtest ${CMAKE_THREAD_LIBS_INIT})
    add_test(${OUTFILE} ${OUTFILE})
else()
    set(CMAKE_FIND_LIBRARY_SUFFIXES ".a")
    set(BUILD_SHARED_LIBRARIES OFF)
    set(CMAKE_EXE_LINKER_FLAGS "-static")
    add_executable(${OUTFILE} ${MESSAGE_CONTENT_CHECKER_SOURCES} ${MESSAGE_CONTENT_CHECKER_MAIN_SOURCES})
    include_directories(${MESSAGE_CONTENT_CHECKER_INCLUDE_DIRECTORIES} ${SACKS_DIR_TO_INCLUDE})
    target_link_libraries(${OUTFILE} APRG_COMMON)
endif()
