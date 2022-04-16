cmake_minimum_required(VERSION 3.16)

#set project details
project(DMeasTimerStack C CXX)
set(OUTFILE ${PROJECT_NAME})
set(DMEAS_TIMER_STACK_DIR ${CMAKE_CURRENT_SOURCE_DIR})

#Comment out TEST_MODE to build static executable, other cmakes check this
set(TEST_MODE "ON")

#Locate APRG Directory first because its used on other cmakes
get_filename_component(ABSOLUTE_CURRENT_DIR "${CMAKE_CURRENT_LIST_DIR}" ABSOLUTE)
get_filename_component(CURRENT_DIR_NAME "$${ABSOLUTE_CURRENT_DIR}" NAME)
while(NOT ${CURRENT_DIR_NAME} MATCHES "APRG")
    get_filename_component(ABSOLUTE_CURRENT_DIR "${ABSOLUTE_CURRENT_DIR}/.." ABSOLUTE)
    get_filename_component(CURRENT_DIR_NAME "$${ABSOLUTE_CURRENT_DIR}" NAME)
endwhile()
set(APRG_DIR ${ABSOLUTE_CURRENT_DIR})

#Assign common flags, definitions and macros
include(${APRG_DIR}/AprgCMakeHelpers/CommonFlags.cmake)
include(${APRG_DIR}/AprgCMakeHelpers/CommonDefinitions.cmake)
include(${APRG_DIR}/AprgCMakeHelpers/FileAndDirectoryMacros.cmake)

#Include other projects
include(${APRG_DIR}/gtest/AprgCmakeInclude/gtest.cmake)
include(${APRG_DIR}/AprgCommon/AprgCmakeInclude/AprgCommon.cmake)

#Add files and directories
include(${DMEAS_TIMER_STACK_DIR}/cmake/FilesAndDirectories.cmake)

#Assign Sack Directory
set(SackDirectory "N:/Branches/ControlPlane/sbts1/tcom")

set(SACKS_DIR_TO_INCLUDE
    ${SackDirectory}/I_Interface/Private/SC_TCOM/Temp
    ${SackDirectory}/I_Interface/Global_Env/Definitions
    ${SackDirectory}/I_Interface/Global_Env/Messages
    ${SackDirectory}/I_Interface/Application_Env
    ${SackDirectory}/I_Interface/Application_Env/Wn_Env/Bs_Env
    ${SackDirectory}/I_Interface/Application_Env/Definitions
    ${SackDirectory}/I_Interface/Application_Env/Wn_Env/Bs_Env/Definitions
    ${SackDirectory}/I_Interface/Application_Env/Messages
    ${SackDirectory}/I_Interface/Application_Env/Interfaces
    ${SackDirectory}/I_Interface/Application_Env/Wn_Env/Bs_Env/Messages
    ${SackDirectory}/I_Interface/Application_Env/Wn_Env/Bs_Env/Ppc_Env/Definitions
    ${SackDirectory}/I_Interface/Application_Env/Wn_Env/Bs_Env/Ppc_Env/Messages
    ${SackDirectory}/I_Interface/Application_Env/Wn_Env/Bs_Env/Dsp_Env/Definitions
    ${SackDirectory}/I_Interface/Application_Env/Wn_Env/Bs_Env/Dsp_Env/Messages
    ${SackDirectory}/I_Interface/Private/SC_TCOM/Definitions
    ${SackDirectory}/I_Interface/Private/SC_TCOM/Messages
    ${SackDirectory}/I_Interface/Platform_Env/CCS_ENV/MCU/Definitions
    ${SackDirectory}/I_Interface/Platform_Env/CCS_ENV/MCU/Messages
    ${SackDirectory}/I_Interface/Platform_Env/CCS_ENV/MCU/ServiceInterface
    ${SackDirectory}/I_Interface/Platform_Env/CCS_ENV/COMMON/Definitions
    ${SackDirectory}/I_Interface/Platform_Env/CCS_ENV/COMMON/Messages
    ${SackDirectory}/I_Interface/Platform_Env/CCS_ENV/COMMON/ServiceInterface
    ${SackDirectory}/I_Interface/Platform_Env/CCS_ENV/DSP/Definitions
    ${SackDirectory}/I_Interface/Platform_Env/Messages
    ${SackDirectory}/I_Interface/Platform_Env/MCUHWAPI_ENV/Definitions
    ${SackDirectory}/I_Interface/Platform_Env/MCUHWAPI_ENV/Messages
    ${SackDirectory}/I_Interface/Platform_Env/DSPHWAPI_ENV/Definitions
    ${SackDirectory}/I_Interface/Platform_Env/DSPHWAPI_ENV/Messages
    ${SackDirectory}/I_Interface/Platform_Env/UPHWAPI_ENV/DSP_AND_RTHWAPI_ENV/COMMON_ENV/Definitions
    ${SackDirectory}/I_Interface/Platform_Env/UPHWAPI_ENV/DSP_AND_RTHWAPI_ENV/COMMON_ENV/Messages
    ${SackDirectory}/I_Interface/Platform_Env/UPHWAPI_ENV/DSPHWAPI_ENV/FARADAY_ENV/Definitions
    ${SackDirectory}/I_Interface/Platform_Env/Definitions
)

set(TCOM_PRIVATE_SACK_DIRECTORY ${SackDirectory}/I_Interface)
PRINT_STATUS("Looking for TCOM_PRIVATE_SACKS directories in: [${TCOM_PRIVATE_SACK_DIRECTORY}]")
GET_SUB_DIRECTORY_LIST(TCOM_PRIVATE_SACK_DIRECTORY_LIST ${TCOM_PRIVATE_SACK_DIRECTORY})
GET_SOURCE_FILES_FROM_DIRECTORIES(TCOM_PRIVATE_SACKS TCOM_PRIVATE_SACK_DIRECTORY_LIST)

set(BTS_SACK_DIRECTORY ${SackDirectory}/I_Interface)
PRINT_STATUS("Looking for BTS_SACKS directories in: [${BTS_SACK_DIRECTORY}]")
GET_SUB_DIRECTORY_LIST(BTS_SACK_DIRECTORY_LIST ${BTS_SACK_DIRECTORY})
GET_SOURCE_FILES_FROM_DIRECTORIES(BTS_SACKS BTS_SACK_DIRECTORY_LIST)

#Do final steps
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
