#Assign AprgCommon directory, this needs aprg directory
set(APRG_BOOLEAN_ALGEBRA_DIR ${APRG_DIR}/AprgBooleanAlgebra/AprgBooleanAlgebra/)

#Include APRG_COMMON files and directories
include(${APRG_BOOLEAN_ALGEBRA_DIR}/cmake/FilesAndDirectories.cmake)

include_directories(${APRG_BOOLEAN_ALGEBRA_INCLUDE_DIRECTORIES})
add_library(APRG_BOOLEAN_ALGEBRA ${APRG_BOOLEAN_ALGEBRA_SOURCES})
