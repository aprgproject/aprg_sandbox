cmake_minimum_required(VERSION 2.8)
project(DMeasTimerStack C CXX)

set(OUTFILE ${PROJECT_NAME})

#Comment out TEST_MODE to build static executable
set(TEST_MODE "ON")

#Assign APRG Directory
set(APRG_DIR ${CMAKE_CURRENT_SOURCE_DIR}/../../)
set(DMEAS_TIMER_STACK_DIR ${CMAKE_CURRENT_SOURCE_DIR})

#Assign Flags
include(${APRG_DIR}/AprgCMakeHelpers/CommonFlags.cmake)

#Assign Definitions
include(${APRG_DIR}/AprgCMakeHelpers/CommonDefinitions.cmake)

#Include gtest, this needs APRG Directory
include(${APRG_DIR}/gtest/AprgCmakeInclude/gtest.cmake)

#Include AprgCommon, this needs APRG Directory
include(${APRG_DIR}/AprgCommon/AprgCmakeInclude/AprgCommon.cmake)

#Include AprgCMakeHelpers, this needs APRG Directory
include(${APRG_DIR}/AprgCMakeHelpers/FileAndDirectoryMacros.cmake)

#Add files and directories
include(${DMEAS_TIMER_STACK_DIR}/cmake/FilesAndDirectories.cmake)

#Assign Sack Directory
set(SackDirectory "D:/Branches/SubsystemFrameworkImprovement/subsystemTemplate")

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

set(TCOM_PRIVATE_SACK_DIRECTORY ${SackDirectory}/I_Interface)
PRINT_STATUS("Looking for TCOM_PRIVATE_SACKS directories in: [${TCOM_PRIVATE_SACK_DIRECTORY}]")
GET_SUB_DIRECTORY_LIST(TCOM_PRIVATE_SACK_DIRECTORY_LIST ${TCOM_PRIVATE_SACK_DIRECTORY})
GET_SOURCE_FILES_FROM_DIRECTORIES(TCOM_PRIVATE_SACKS TCOM_PRIVATE_SACK_DIRECTORY_LIST)

set(BTS_SACK_DIRECTORY ${SackDirectory}/wbts_integration/I_Interface)
PRINT_STATUS("Looking for BTS_SACKS directories in: [${BTS_SACK_DIRECTORY}]")
GET_SUB_DIRECTORY_LIST(BTS_SACK_DIRECTORY_LIST ${BTS_SACK_DIRECTORY})
GET_SOURCE_FILES_FROM_DIRECTORIES(BTS_SACKS BTS_SACK_DIRECTORY_LIST)

if (TEST_MODE)
    add_executable(${OUTFILE} ${DMEAS_TIMER_STACK_SOURCES_AND_TESTS} ${TCOM_PRIVATE_SACKS} ${BTS_SACKS})
    include_directories(${DMEAS_TIMER_STACK_INCLUDE_DIRECTORIES} ${DMEAS_TIMER_STACK_TEST_INCLUDE_DIRECTORIES} ${SACKS_DIR_TO_INCLUDE} ${GTEST_INCLUDE_DIRS})
    target_link_libraries(${OUTFILE} ${CMAKE_THREAD_LIBS_INIT} APRG_COMMON gtest ${CMAKE_THREAD_LIBS_INIT})
    add_test(${OUTFILE} ${OUTFILE})
else()
    set(CMAKE_FIND_LIBRARY_SUFFIXES ".a")
    set(BUILD_SHARED_LIBRARIES OFF)
    set(CMAKE_EXE_LINKER_FLAGS "-static")
    add_executable(${OUTFILE} ${DMEAS_TIMER_STACK_SOURCES} ${DMEAS_TIMER_STACK_MAIN_SOURCES} ${TCOM_PRIVATE_SACKS} ${BTS_SACKS})
    include_directories(${DMEAS_TIMER_STACK_INCLUDE_DIRECTORIES} ${SACKS_DIR_TO_INCLUDE})
    target_link_libraries(${OUTFILE} APRG_COMMON)
endif()
