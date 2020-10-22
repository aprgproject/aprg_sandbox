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

set(SOURCES
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
    src/Common/Sacks/Sacks.cpp
    src/Common/Sacks/Sacks.hpp
    src/Common/Timers/Timers.cpp
    src/Common/Timers/Timers.hpp
    src/Common/Timers/TimerType.hpp
    src/Common/Utils/EnumHelper.cpp
    src/Common/Utils/EnumHelper.hpp
    src/Common/Environment.cpp
    src/Common/Environment.hpp
    src/EditableFiles/EditAddComponent.hpp
    src/EditableFiles/EditComponentName.hpp
    src/EditableFiles/EditComponentsIncludes.hpp
    src/EditableFiles/EditMessageName.hpp
    src/EditableFiles/EditSacksIncludes.hpp
    src/EditableFiles/EditWrapMessage.hpp
)

set(MAIN_SOURCES
    src/Common/main.cpp
)

set(TESTS
    tst/Common/InternalTests_unit.cpp
)

set(INCLUDE_DIRECTORIES
    src/
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
