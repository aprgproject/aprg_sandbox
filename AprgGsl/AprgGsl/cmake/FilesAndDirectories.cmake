include(${APRG_DIR}/AprgCMakeHelpers/FileAndDirectoryMacros.cmake)
include(${APRG_DIR}/AprgCMakeHelpers/PrintMacros.cmake)

set(APRG_GSL_SOURCE_DIRECTORY
    ${APRG_GSL_DIR}/src
)

set(APRG_GSL_TEST_DIRECTORY
    ${APRG_GSL_DIR}/tst
)

set(APRG_GSL_INCLUDE_DIRECTORIES
    ${APRG_GSL_SOURCE_DIRECTORY}
)

set(APRG_GSL_TEST_INCLUDE_DIRECTORIES
    ${APRG_GSL_TEST_DIRECTORY}
)

PRINT_STATUS("Looking for SRC directories in: [${APRG_GSL_SOURCE_DIRECTORY}]")
GET_SUB_DIRECTORY_LIST(APRG_GSL_SOURCE_DIRECTORY_LIST ${APRG_GSL_SOURCE_DIRECTORY})
GET_SOURCE_FILES_FROM_DIRECTORIES(APRG_GSL_SOURCES APRG_GSL_SOURCE_DIRECTORY_LIST)

PRINT_STATUS("Looking for TST directories in: [${APRG_GSL_TEST_DIRECTORY}]")
GET_SUB_DIRECTORY_LIST(APRG_GSL_TEST_DIRECTORY_LIST ${APRG_GSL_TEST_DIRECTORY})
GET_SOURCE_FILES_FROM_DIRECTORIES(APRG_GSL_TESTS APRG_GSL_TEST_DIRECTORY_LIST)

set(APRG_GSL_SOURCES_AND_TESTS
    ${APRG_GSL_SOURCES}
    ${APRG_GSL_TESTS})