set(FESTER_ROBOT_SOURCE_DIRECTORY
    ${FESTER_ROBOT_DIR}/src
)

set(FESTER_ROBOT_TEST_DIRECTORY
    ${FESTER_ROBOT_DIR}/tst
)

set(FESTER_ROBOT_MAIN_DIRECTORY
    ${FESTER_ROBOT_DIR}/main
)

set(FESTER_ROBOT_INCLUDE_DIRECTORIES
    ${FESTER_ROBOT_SOURCE_DIRECTORY}
)

set(FESTER_ROBOT_TEST_INCLUDE_DIRECTORIES
    ${FESTER_ROBOT_TEST_DIRECTORY}
)

PRINT_STATUS("Looking for SRC directories in: [${FESTER_ROBOT_SOURCE_DIRECTORY}]")
GET_SUB_DIRECTORY_LIST(FESTER_ROBOT_SOURCE_DIRECTORY_LIST ${FESTER_ROBOT_SOURCE_DIRECTORY})
GET_SOURCE_FILES_FROM_DIRECTORIES(FESTER_ROBOT_SOURCES FESTER_ROBOT_SOURCE_DIRECTORY_LIST)

PRINT_STATUS("Looking for TST directories in: [${FESTER_ROBOT_TEST_DIRECTORY}]")
GET_SUB_DIRECTORY_LIST(FESTER_ROBOT_TEST_DIRECTORY_LIST ${FESTER_ROBOT_TEST_DIRECTORY})
GET_SOURCE_FILES_FROM_DIRECTORIES(FESTER_ROBOT_TESTS FESTER_ROBOT_TEST_DIRECTORY_LIST)

PRINT_STATUS("Looking for MAIN directories in: [${FESTER_ROBOT_MAIN_DIRECTORY}]")
GET_SUB_DIRECTORY_LIST(FESTER_ROBOT_MAIN_DIRECTORY_LIST ${FESTER_ROBOT_MAIN_DIRECTORY})
GET_SOURCE_FILES_FROM_DIRECTORIES(FESTER_ROBOT_MAIN_SOURCES FESTER_ROBOT_MAIN_DIRECTORY_LIST)

set(FESTER_ROBOT_SOURCES_AND_TESTS
    ${FESTER_ROBOT_SOURCES}
    ${FESTER_ROBOT_TESTS}
)
