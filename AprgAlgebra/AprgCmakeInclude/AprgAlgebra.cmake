#Assign AprgCommon directory, this needs aprg directory
set(APRG_ALGEBRA_DIR ${APRG_DIR}/AprgAlgebra/AprgAlgebra/)

#Include APRG_COMMON files and directories
include(${APRG_ALGEBRA_DIR}/cmake/FilesAndDirectories.cmake)

include_directories(${APRG_ALGEBRA_INCLUDE_DIRECTORIES})
add_library(APRG_ALGEBRA ${APRG_ALGEBRA_SOURCES})
