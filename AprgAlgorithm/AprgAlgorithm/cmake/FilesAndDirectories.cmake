include(${APRG_DIR}/AprgCMakeHelpers/FileAndDirectoryMacros.cmake)
include(${APRG_DIR}/AprgCMakeHelpers/PrintMacros.cmake)

set(APRG_ALGORITHM_SOURCE_DIRECTORY
    ${APRG_ALGORITHM_DIR}/src
)

set(APRG_ALGORITHM_TEST_DIRECTORY
    ${APRG_ALGORITHM_DIR}/tst
)

set(APRG_ALGORITHM_INCLUDE_DIRECTORIES
    ${APRG_ALGORITHM_SOURCE_DIRECTORY}
)

set(APRG_ALGORITHM_TEST_INCLUDE_DIRECTORIES
    ${APRG_ALGORITHM_TEST_DIRECTORY}
)

PRINT_STATUS("Looking for SRC directories in: [${APRG_ALGORITHM_SOURCE_DIRECTORY}]")
GET_SUB_DIRECTORY_LIST(APRG_ALGORITHM_SOURCE_DIRECTORY_LIST ${APRG_ALGORITHM_SOURCE_DIRECTORY})
GET_SOURCE_FILES_FROM_DIRECTORIES(APRG_ALGORITHM_SOURCES APRG_ALGORITHM_SOURCE_DIRECTORY_LIST)

PRINT_STATUS("Looking for TST directories in: [${APRG_ALGORITHM_TEST_DIRECTORY}]")
GET_SUB_DIRECTORY_LIST(APRG_ALGORITHM_TEST_DIRECTORY_LIST ${APRG_ALGORITHM_TEST_DIRECTORY})
GET_SOURCE_FILES_FROM_DIRECTORIES(APRG_ALGORITHM_TESTS APRG_ALGORITHM_TEST_DIRECTORY_LIST)

set(APRG_ALGORITHM_SOURCES_AND_TESTS
    ${APRG_ALGORITHM_SOURCES}
    ${APRG_ALGORITHM_TESTS})