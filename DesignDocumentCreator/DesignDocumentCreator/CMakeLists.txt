cmake_minimum_required(VERSION 2.8)
project(DesignDocumentCreator C CXX)

set(OUTFILE ${PROJECT_NAME})

#Comment out TEST_MODE to build static executable
set(TEST_MODE "ON")

#Assign APRG Directory
set(APRG_DIR ${CMAKE_CURRENT_SOURCE_DIR}/../../)

#Assign Flags do not include -mwindows to make a console build
set(CMAKE_C_FLAGS "-Wall -Wextra -pedantic --coverage -std=c99")
set(CMAKE_CXX_FLAGS "-Wall -Wextra -pedantic --coverage -std=c++11")

#Include aprgCommon, this needs APRG Directory
include(${APRG_DIR}/AprgCommon/AprgCmakeInclude/AprgCommon.cmake)

#Include gTest, this needs APRG Directory
include(${APRG_DIR}/gtest-1.7.0/AprgCmakeInclude/gtest.cmake)

#Include AprgCMakeHelpers, this needs APRG Directory
include(${APRG_DIR}/AprgCMakeHelpers/cmake/Macros.cmake)

#RAN3374 Files
set(RAN3374_SOURCES
    src/RAN3374/Components/DMGR.cpp
    src/RAN3374/Components/DMGR.hpp
    src/RAN3374/Components/GRM.cpp
    src/RAN3374/Components/GRM.hpp
    src/RAN3374/Components/LRM.cpp
    src/RAN3374/Components/LRM.hpp
    src/RAN3374/Components/Rake.cpp
    src/RAN3374/Components/Rake.hpp
    src/RAN3374/Components/RF.cpp
    src/RAN3374/Components/RF.hpp
    src/RAN3374/Components/TLH.cpp
    src/RAN3374/Components/TLH.hpp
    src/RAN3374/Components/TOAM.cpp
    src/RAN3374/Components/TOAM.hpp
    src/RAN3374/Components/WRC.cpp
    src/RAN3374/Components/WRC.hpp
    src/RAN3374/FeatureSpecificFiles/AddComponent.hpp
    src/RAN3374/FeatureSpecificFiles/ComponentName.hpp
    src/RAN3374/FeatureSpecificFiles/ComponentsIncludes.hpp
    src/RAN3374/FeatureSpecificFiles/ConvertToStringComponentName.hpp
    src/RAN3374/FeatureSpecificFiles/ConvertToStringMessageName.hpp
    src/RAN3374/FeatureSpecificFiles/MessageName.hpp
    src/RAN3374/FeatureSpecificFiles/Sacks.hpp
    src/RAN3374/FeatureSpecificFiles/WrapMessage.hpp
    src/RAN3374/Sacks/Sacks.hpp
    src/RAN3374/Sacks/SupplementarySacks.hpp
)
set(RAN3374_TESTS
    tst/RAN3374/RAN3374_unit.cpp
)

#Supplementary sacks
set(SUPPLEMENTARY_SACK_DIR
    src/Common/Sacks/SupplementarySacks
    src/RAN3374/Sacks/SupplementarySacks
)
#Use MACRO_GET_FILES to find supplementary files
MACRO_GET_FILES(SUPPLEMENTARY_SACKS SUPPLEMENTARY_SACK_DIR)

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
    src/Common/Sacks/SupplementarySacks.hpp
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
set(FEATURE_SPECIFIC_SOURCES
    src/FeatureSpecificFiles/AddComponent.hpp
    src/FeatureSpecificFiles/ComponentName.hpp
    src/FeatureSpecificFiles/ComponentsIncludes.hpp
    src/FeatureSpecificFiles/ConvertToStringComponentName.hpp
    src/FeatureSpecificFiles/ConvertToStringMessageName.hpp
    src/FeatureSpecificFiles/MessageName.hpp
    src/FeatureSpecificFiles/Sacks.hpp
    src/FeatureSpecificFiles/WrapMessage.hpp
)

#Collecting files and directories
set(SOURCES
    ${COMMON_SOURCES}
    ${FEATURE_SPECIFIC_SOURCES}
    ${RAN3374_SOURCES}
    ${SUPPLEMENTARY_SACKS}
)

set(MAIN_SOURCES
    src/Common/main.cpp
)

set(INTERNAL_TESTS
    tst/Common/InternalTests_unit.cpp
)

set(TESTS
    ${INTERNAL_TESTS}
    ${RAN3374_TESTS}
)

set(INCLUDE_DIRECTORIES
    src/
    ${SUPPLEMENTARY_SACK_DIR}
)

if (TEST_MODE)
    add_executable(${OUTFILE} ${SOURCES} ${TESTS})
    include_directories(${INCLUDE_DIRECTORIES} ${GTEST_INCLUDE_DIRS})
    target_link_libraries(${OUTFILE} gtest APRG_COMMON ${CMAKE_THREAD_LIBS_INIT})
    add_test(${OUTFILE} ${OUTFILE})
else()
    set(CMAKE_FIND_LIBRARY_SUFFIXES ".a")
    set(BUILD_SHARED_LIBRARIES OFF)
    set(CMAKE_EXE_LINKER_FLAGS "-static")
    add_executable(${OUTFILE} ${SOURCES} ${MAIN_SOURCES})
    include_directories(${INCLUDE_DIRECTORIES})
    target_link_libraries(${OUTFILE} APRG_COMMON)
endif()
