cmake_minimum_required(VERSION 2.8)
project(DesignDocumentCreator C CXX)

set(OUTFILE ${PROJECT_NAME})

#Comment out TEST_MODE to build static executable
set(TEST_MODE "ON")

#Assign APRG Directory
set(APRG_DIR ${CMAKE_CURRENT_SOURCE_DIR}/../../)
set(DD_CREATOR_DIR ${CMAKE_CURRENT_SOURCE_DIR})

#Assign DesignDocumentCreatorDirectory
set(DesignDocumentCreatorDirectory ${CMAKE_CURRENT_SOURCE_DIR})

#Assign Flags
include(${APRG_DIR}/AprgCMakeHelpers/CommonFlags.cmake)

#Assign Definitions
include(${APRG_DIR}/AprgCMakeHelpers/CommonDefinitions.cmake)
add_definitions(-DCCS_BIG_ENDIAN)

#Include gtest, this needs APRG Directory
include(${APRG_DIR}/gtest/AprgCmakeInclude/gtest.cmake)

#Include AprgCommon, this needs APRG Directory
include(${APRG_DIR}/AprgCommon/AprgCmakeInclude/AprgCommon.cmake)

#Include AprgCMakeHelpers, this needs APRG Directory
include(${APRG_DIR}/AprgCMakeHelpers/FileAndDirectoryMacros.cmake)

#Add files and directories
include(${DD_CREATOR_DIR}/cmake/CommonFilesAndDirectories.cmake)

#Feature include
set(FEATURE_FOLDER "CNI21985")
include(${DD_CREATOR_DIR}/cmake/FeatureFilesAndDirectories.cmake)
add_definitions(-DLOG_LOCATION="${APRG_DIR}/DesignDocumentCreator/DesignDocumentCreatorLogs/RP001749")

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

set(DD_CREATOR_INCLUDE_DIRECTORIES ${DD_CREATOR_DIR}/src ${DD_CREATOR_DIR}/tst)

add_executable(${OUTFILE} ${DD_CREATOR_COMMON_SOURCES_AND_TESTS} ${FEATURE_SOURCES_AND_TESTS} ${TCOM_PRIVATE_SACKS} ${BTS_SACKS})
include_directories(
    ${FEATURE_INCLUDE_DIRECTORIES}
    ${DD_CREATOR_INCLUDE_DIRECTORIES}
    ${SACKS_DIR_TO_INCLUDE}
    ${GTEST_INCLUDE_DIRS}
)
target_link_libraries(${OUTFILE} ${CMAKE_THREAD_LIBS_INIT} APRG_COMMON gtest pthread)
add_test(${OUTFILE} ${OUTFILE})
