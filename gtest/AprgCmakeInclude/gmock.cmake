#This needs aprg directory
include(${APRG_DIR}/gtest/AprgCmakeInclude/SetGTestDirectory.cmake)

set(GOGGLE_MOCK_DIR ${GTEST_DIR}/googlemock)

set(GTEST_INCLUDE_DIRECTORIES
    ${GOGGLE_MOCK_DIR}/include
    ${GOGGLE_MOCK_DIR}/
    )

include_directories(${GTEST_INCLUDE_DIRECTORIES})

add_library(gmock
    ${GOGGLE_MOCK_DIR}/src/gmock-all.cc
    ${GOGGLE_MOCK_DIR}/src/gmock_main.cc
    )
enable_testing(true)
