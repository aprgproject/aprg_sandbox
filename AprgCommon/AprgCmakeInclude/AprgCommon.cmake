#Assign AprgCommon directory, needs aprg directory
set(APRG_COMMON_DIR ${APRG_DIR}/AprgCommon/AprgCommon/)

#Include AprgCommon library
set(APRG_COMMON_INCLUDE_DIRECTORIES
    ${APRG_COMMON_DIR}
    ${APRG_COMMON_DIR}/src
    ${APRG_COMMON_DIR}/src/PathHandlers
)

#Include APRG_COMMON_SOURCES
include(${APRG_COMMON_DIR}/cmake/AprgCommonSources.cmake)

include_directories(${APRG_COMMON_INCLUDE_DIRECTORIES})
add_library(APRG_COMMON ${APRG_COMMON_SOURCES})
