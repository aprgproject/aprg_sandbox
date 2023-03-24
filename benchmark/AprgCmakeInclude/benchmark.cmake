#Assign AprgCommon directory, this needs aprg directory
set(BENCHMARK_DIR ${APRG_DIR}/benchmark/benchmark/)
set(BENCHMARK_FROM_GIT_HUB_DIR ${APRG_DIR}/benchmark/benchmarkFromGitHub/)

#Include APRG_COMMON files and directories
include(${BENCHMARK_DIR}/cmake/FilesAndDirectories.cmake)

include_directories(${BENCHMARK_INCLUDE_DIRECTORIES})
add_library(BENCHMARK ${BENCHMARK_SOURCES})
