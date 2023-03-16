#This needs aprg directory
include(${APRG_DIR}/gtest/AprgCmakeInclude/SetGTestDirectory.cmake)

set(GOOGLE_TEST_DIR ${GTEST_DIR}/googletest)

find_package(Threads)
if (CMAKE_USE_PTHREADS_INIT)  # The pthreads library is available and allowed.
    set(gtest_disable_pthread ON)
else()
    set(gtest_disable_pthread ON)
endif()

set(GTEST_INCLUDE_DIRECTORIES
    ${GOOGLE_TEST_DIR}/include
    ${GOOGLE_TEST_DIR}/
    )

include_directories(${GTEST_INCLUDE_DIRECTORIES})

add_library(gtest
    ${GOOGLE_TEST_DIR}/src/gtest-all.cc
    ${GOOGLE_TEST_DIR}/src/gtest_main.cc
    )

enable_testing(true)

