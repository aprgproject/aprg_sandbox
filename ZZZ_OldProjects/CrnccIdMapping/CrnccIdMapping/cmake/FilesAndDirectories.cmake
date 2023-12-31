set(CRNCCID_MAPPING_SOURCE_DIRECTORY
    ${CRNCCID_MAPPING_DIR}/src
)

set(CRNCCID_MAPPING_TEST_DIRECTORY
    ${CRNCCID_MAPPING_DIR}/tst
)

set(CRNCCID_MAPPING_INCLUDE_DIRECTORIES
    ${CRNCCID_MAPPING_SOURCE_DIRECTORY}
)

set(CRNCCID_MAPPING_TEST_INCLUDE_DIRECTORIES
    ${CRNCCID_MAPPING_TEST_DIRECTORY}
)

PRINT_STATUS("Looking for SRC directories in: [${CRNCCID_MAPPING_SOURCE_DIRECTORY}]")
GET_SUB_DIRECTORY_LIST(CRNCCID_MAPPING_SOURCE_DIRECTORY_LIST ${CRNCCID_MAPPING_SOURCE_DIRECTORY})
GET_SOURCE_FILES_FROM_DIRECTORIES(CRNCCID_MAPPING_SOURCES CRNCCID_MAPPING_SOURCE_DIRECTORY_LIST)

PRINT_STATUS("Looking for TST directories in: [${CRNCCID_MAPPING_TEST_DIRECTORY}]")
GET_SUB_DIRECTORY_LIST(CRNCCID_MAPPING_TEST_DIRECTORY_LIST ${CRNCCID_MAPPING_TEST_DIRECTORY})
GET_SOURCE_FILES_FROM_DIRECTORIES(CRNCCID_MAPPING_TESTS CRNCCID_MAPPING_TEST_DIRECTORY_LIST)

set(CRNCCID_MAPPING_SOURCES_AND_TESTS
    ${CRNCCID_MAPPING_SOURCES}
    ${CRNCCID_MAPPING_TESTS}
)
