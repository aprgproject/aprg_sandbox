#This does not work improve on this later on

cmake_minimum_required(VERSION 2.8)
project(gtest)

set(GTEST_DIR ${APRG_DIR}/gtest/gtest/)
set(GOOGLE_MOCK_DIR ${GTEST_DIR}/googlemock)
set(GOOGLE_TEST_DIR ${GTEST_DIR}/googletest)

include_directories(
    ${GOOGLE_TEST_DIR}/include
    ${GOOGLE_MOCK_DIR}/include
    ${GOOGLE_TEST_DIR}/
    ${GOOGLE_MOCK_DIR}/
    )

add_subdirectory(${GTEST_DIR} gtest)

target_sources(gtest PRIVATE ${APRG_DIR}/gtest/main/main.cpp)
