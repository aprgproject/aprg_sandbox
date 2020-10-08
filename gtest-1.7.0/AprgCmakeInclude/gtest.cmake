#Assign gtest directory, this needs aprg directory
set(GTEST_DIR ${APRG_DIR}/gtest-1.7.0/gtest-1.7.0/)

################################################################################# GTest
# See: http://code.google.com/p/googletest/
################################################################################
find_package(Threads)if (CMAKE_USE_PTHREADS_INIT)  # The pthreads library is available and allowed.
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -DGTEST_HAS_PTHREAD=1")
else()
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -DGTEST_HAS_PTHREAD=0")
endif()

set(GTEST_INCLUDE_DIRECTORIES
    ${GTEST_DIR}/include
    ${GTEST_DIR}    ${GTEST_DIR}/src
)
include_directories(${GTEST_INCLUDE_DIRECTORIES})
add_library(gtest ${GTEST_DIR}/src/gtest-all.cc ${GTEST_DIR}/src/gtest_main.cc)
enable_testing(true)
