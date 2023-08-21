set(DMEAS_TIMER_STACK_SOURCE_DIRECTORY
    ${DMEAS_TIMER_STACK_DIR}/src
)
set(DMEAS_TIMER_STACK_TEST_DIRECTORY
    ${DMEAS_TIMER_STACK_DIR}/tst
)
set(DMEAS_TIMER_STACK_MAIN_DIRECTORY
    ${DMEAS_TIMER_STACK_DIR}/main
)

set(DMEAS_TIMER_STACK_INCLUDE_DIRECTORIES
    ${DMEAS_TIMER_STACK_SOURCE_DIRECTORY}
)

set(DMEAS_TIMER_STACK_TEST_INCLUDE_DIRECTORIES
    ${DMEAS_TIMER_STACK_TEST_DIRECTORY}
)

PRINT_STATUS("Looking for SRC directories in: [${DMEAS_TIMER_STACK_SOURCE_DIRECTORY}]")
GET_SUB_DIRECTORY_LIST(DMEAS_TIMER_STACK_SOURCE_DIRECTORY_LIST ${DMEAS_TIMER_STACK_SOURCE_DIRECTORY})
GET_SOURCE_FILES_FROM_DIRECTORIES(DMEAS_TIMER_STACK_SOURCES DMEAS_TIMER_STACK_SOURCE_DIRECTORY_LIST)

PRINT_STATUS("Looking for TST directories in: [${DMEAS_TIMER_STACK_TEST_DIRECTORY}]")
GET_SUB_DIRECTORY_LIST(DMEAS_TIMER_STACK_TEST_DIRECTORY_LIST ${DMEAS_TIMER_STACK_TEST_DIRECTORY})
GET_SOURCE_FILES_FROM_DIRECTORIES(DMEAS_TIMER_STACK_TESTS DMEAS_TIMER_STACK_TEST_DIRECTORY_LIST)

PRINT_STATUS("Looking for MAIN directories in: [${DMEAS_TIMER_STACK_MAIN_DIRECTORY}]")
GET_SUB_DIRECTORY_LIST(DMEAS_TIMER_STACK_MAIN_DIRECTORY_LIST ${DMEAS_TIMER_STACK_MAIN_DIRECTORY})
GET_SOURCE_FILES_FROM_DIRECTORIES(DMEAS_TIMER_STACK_MAIN_SOURCES DMEAS_TIMER_STACK_MAIN_DIRECTORY_LIST)

set(DMEAS_TIMER_STACK_SOURCES_AND_TESTS
    ${DMEAS_TIMER_STACK_SOURCES}
    ${DMEAS_TIMER_STACK_TESTS}
)
