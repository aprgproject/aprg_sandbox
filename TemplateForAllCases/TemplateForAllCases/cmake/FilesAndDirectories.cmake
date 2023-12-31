set(TEMPLATE_FOR_ALL_CASES_SOURCE_DIRECTORY
    ${TEMPLATE_FOR_ALL_CASES_DIR}/src
)

set(TEMPLATE_FOR_ALL_CASES_TEST_DIRECTORY
    ${TEMPLATE_FOR_ALL_CASES_DIR}/tst
)

set(TEMPLATE_FOR_ALL_CASES_MAIN_DIRECTORY
    ${TEMPLATE_FOR_ALL_CASES_DIR}/main
)

set(TEMPLATE_FOR_ALL_CASES_INCLUDE_DIRECTORIES
    ${TEMPLATE_FOR_ALL_CASES_SOURCE_DIRECTORY}
)

set(TEMPLATE_FOR_ALL_CASES_TEST_INCLUDE_DIRECTORIES
    ${TEMPLATE_FOR_ALL_CASES_TEST_DIRECTORY}
)

PRINT_STATUS("Looking for SRC directories in: [${TEMPLATE_FOR_ALL_CASES_SOURCE_DIRECTORY}]")
GET_SUB_DIRECTORY_LIST(TEMPLATE_FOR_ALL_CASES_SOURCE_DIRECTORY_LIST ${TEMPLATE_FOR_ALL_CASES_SOURCE_DIRECTORY})
GET_SOURCE_FILES_FROM_DIRECTORIES(TEMPLATE_FOR_ALL_CASES_SOURCES TEMPLATE_FOR_ALL_CASES_SOURCE_DIRECTORY_LIST)

PRINT_STATUS("Looking for TST directories in: [${TEMPLATE_FOR_ALL_CASES_TEST_DIRECTORY}]")
GET_SUB_DIRECTORY_LIST(TEMPLATE_FOR_ALL_CASES_TEST_DIRECTORY_LIST ${TEMPLATE_FOR_ALL_CASES_TEST_DIRECTORY})
GET_SOURCE_FILES_FROM_DIRECTORIES(TEMPLATE_FOR_ALL_CASES_TESTS TEMPLATE_FOR_ALL_CASES_TEST_DIRECTORY_LIST)

PRINT_STATUS("Looking for MAIN directories in: [${TEMPLATE_FOR_ALL_CASES_MAIN_DIRECTORY}]")
GET_SUB_DIRECTORY_LIST(TEMPLATE_FOR_ALL_CASES_MAIN_DIRECTORY_LIST ${TEMPLATE_FOR_ALL_CASES_MAIN_DIRECTORY})
GET_SOURCE_FILES_FROM_DIRECTORIES(TEMPLATE_FOR_ALL_CASES_MAIN_SOURCES TEMPLATE_FOR_ALL_CASES_MAIN_DIRECTORY_LIST)

set(TEMPLATE_FOR_ALL_CASES_SOURCES_AND_TESTS
    ${TEMPLATE_FOR_ALL_CASES_SOURCES}
    ${TEMPLATE_FOR_ALL_CASES_TESTS}
)
