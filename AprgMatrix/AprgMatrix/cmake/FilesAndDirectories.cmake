include(${APRG_DIR}/AprgCMakeHelpers/FileAndDirectoryMacros.cmake)
include(${APRG_DIR}/AprgCMakeHelpers/PrintMacros.cmake)

set(APRG_MATRIX_SOURCE_DIRECTORY
    ${APRG_MATRIX_DIR}/src
)

set(APRG_MATRIX_TEST_DIRECTORY
    ${APRG_MATRIX_DIR}/tst
)

set(APRG_MATRIX_INCLUDE_DIRECTORIES
    ${APRG_MATRIX_SOURCE_DIRECTORY}
)

set(APRG_MATRIX_TEST_INCLUDE_DIRECTORIES
    ${APRG_MATRIX_TEST_DIRECTORY}
)

PRINT_STATUS("Looking for SRC directories in: [${APRG_MATRIX_SOURCE_DIRECTORY}]")
GET_SUB_DIRECTORY_LIST(APRG_MATRIX_SOURCE_DIRECTORY_LIST ${APRG_MATRIX_SOURCE_DIRECTORY})
GET_SOURCE_FILES_FROM_DIRECTORIES(APRG_MATRIX_SOURCES APRG_MATRIX_SOURCE_DIRECTORY_LIST)

PRINT_STATUS("Looking for TST directories in: [${APRG_MATRIX_TEST_DIRECTORY}]")
GET_SUB_DIRECTORY_LIST(APRG_MATRIX_TEST_DIRECTORY_LIST ${APRG_MATRIX_TEST_DIRECTORY})
GET_SOURCE_FILES_FROM_DIRECTORIES(APRG_MATRIX_TESTS APRG_MATRIX_TEST_DIRECTORY_LIST)

set(APRG_MATRIX_SOURCES_AND_TESTS
    ${APRG_MATRIX_SOURCES}
    ${APRG_MATRIX_TESTS}
)
