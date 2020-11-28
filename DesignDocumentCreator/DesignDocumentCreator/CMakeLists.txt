cmake_minimum_required(VERSION 2.8)
project(DesignDocumentCreator C CXX)

set(OUTFILE ${PROJECT_NAME})

#Comment out TEST_MODE to build static executable
set(TEST_MODE "ON")

#Assign APRG Directory
set(APRG_DIR ${CMAKE_CURRENT_SOURCE_DIR}/../../)

#Assign DesignDocumentCreatorDirectory
set(DesignDocumentCreatorDirectory ${CMAKE_CURRENT_SOURCE_DIR})

#Assign Flags do not include -mwindows to make a console build
set(CMAKE_C_FLAGS "-Wall -Wextra -pedantic --coverage -std=c99")
set(CMAKE_CXX_FLAGS "-Wall -Wextra -pedantic --coverage -std=c++11")
if(WIN32)
    #add -mwindows for windows GUI, do not add for console build
    #set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -mwindows")
    #set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -mwindows")
endif()

#Assign Definitions
add_definitions(-DAPRG_DIR="${APRG_DIR}")

#Include aprgCommon, this needs APRG Directory
include(${APRG_DIR}/AprgCommon/AprgCmakeInclude/AprgCommon.cmake)

#Include gTest, this needs APRG Directory
include(${APRG_DIR}/gtest-1.7.0/AprgCmakeInclude/gtest.cmake)

#Include AprgCMakeHelpers, this needs APRG Directory
include(${APRG_DIR}/AprgCMakeHelpers/cmake/Macros.cmake)

#RAN3374
include(${DesignDocumentCreatorDirectory}/cmake/CNI21985.cmake)

#Assign Sack Directory
set(SackDirectory "D:/Branches/trunk")
#Sacks
set(SACKS_DIR_TO_INCLUDE
    ${SackDirectory}/I_Interface/Private/SC_TCOM/Temp    ${SackDirectory}/wbts_integration/I_Interface/Global_Env/Definitions
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
MACRO_GET_ALL_SOURCES(${SackDirectory}/I_Interface TCOM_PRIVATE_SACKS)
MACRO_GET_ALL_SOURCES(${SackDirectory}/wbts_integration/I_Interface BTS_SACKS)

#Sources
set(COMMON_SOURCES
    src/Common/Components/Component.cpp
    src/Common/Components/Component.hpp
    src/Common/Components/ComponentName.hpp
    src/Common/Components/Components.cpp
    src/Common/Components/Components.hpp
    src/Common/Components/SampleComponent.cpp
    src/Common/Components/SampleComponent.hpp
    src/Common/Events/Events.cpp
    src/Common/Events/Events.hpp
    src/Common/Messages/GenericMessage.hpp
    src/Common/Messages/MessageConverters.hpp
    src/Common/Messages/MessageName.hpp
    src/Common/Messages/Messages.hpp
    src/Common/Messages/MessageWrapper.hpp
    src/Common/Messages/SpecificMessage.hpp
    src/Common/Sacks/Sacks.hpp
    src/Common/Timers/Timers.cpp
    src/Common/Timers/Timers.hpp
    src/Common/Timers/TimerType.hpp
    src/Common/Uml/UmlArrowConfiguration.cpp
    src/Common/Uml/UmlArrowConfiguration.hpp
    src/Common/Uml/UmlConfiguration.cpp
    src/Common/Uml/UmlConfiguration.hpp
    src/Common/Uml/UmlLogger.cpp
    src/Common/Uml/UmlLogger.hpp
    src/Common/Utils/StringHelpers.cpp
    src/Common/Utils/StringHelpers.hpp
    src/Common/Environment.cpp
    src/Common/Environment.hpp
)

#Collecting files and directories
set(SOURCES
    ${COMMON_SOURCES}
    ${FEATURE_SOURCES}
    ${TCOM_PRIVATE_SACKS}
    ${BTS_SACKS}
)
set(MAIN_SOURCES
    src/Common/main.cpp
)
set(INTERNAL_TESTS
    tst/Common/InternalTests_unit.cpp
)

set(TESTS
    ${INTERNAL_TESTS}
    ${FEATURE_TESTS}
)

message(STATUS "TCOM_PRIVATE_SACKS_DIR: ${TCOM_PRIVATE_SACKS_DIR}")message(STATUS "BTS_SACKS_DIR: ${BTS_SACKS_DIR}")

set(INCLUDE_DIRECTORIES
    src/
    ${FEATURE_INCLUDE_DIRECTORIES}
    ${SACKS_DIR_TO_INCLUDE}
)
if (TEST_MODE)
    add_executable(${OUTFILE} ${SOURCES} ${TESTS})
    include_directories(${INCLUDE_DIRECTORIES} ${GTEST_INCLUDE_DIRS})    target_link_libraries(${OUTFILE} gtest APRG_COMMON ${CMAKE_THREAD_LIBS_INIT})
    add_test(${OUTFILE} ${OUTFILE})
else()
    set(CMAKE_FIND_LIBRARY_SUFFIXES ".a")
    set(BUILD_SHARED_LIBRARIES OFF)
    set(CMAKE_EXE_LINKER_FLAGS "-static")
    add_executable(${OUTFILE} ${SOURCES} ${MAIN_SOURCES})
    include_directories(${INCLUDE_DIRECTORIES})
    target_link_libraries(${OUTFILE} APRG_COMMON)
endif()
