#Assign gtest directory, this needs aprg directory
set(GTEST_DIR ${APRG_DIR}/gtest/gtest/)

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
