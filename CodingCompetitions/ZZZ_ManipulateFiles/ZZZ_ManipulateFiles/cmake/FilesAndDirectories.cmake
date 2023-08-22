set(ZZZ_MANIPULATE_FILES_SOURCE_DIRECTORY
    ${ZZZ_MANIPULATE_FILES_DIR}/src
)
set(ZZZ_MANIPULATE_FILES_TEST_DIRECTORY
    ${ZZZ_MANIPULATE_FILES_DIR}/tst
)
set(ZZZ_MANIPULATE_FILES_INCLUDE_DIRECTORIES
    ${ZZZ_MANIPULATE_FILES_SOURCE_DIRECTORY}
)

set(ZZZ_MANIPULATE_FILES_TEST_INCLUDE_DIRECTORIES
    ${ZZZ_MANIPULATE_FILES_TEST_DIRECTORY}
)

PRINT_STATUS("Looking for SRC directories in: [${ZZZ_MANIPULATE_FILES_SOURCE_DIRECTORY}]")
GET_SUB_DIRECTORY_LIST(ZZZ_MANIPULATE_FILES_SOURCE_DIRECTORY_LIST ${ZZZ_MANIPULATE_FILES_SOURCE_DIRECTORY})
GET_SOURCE_FILES_FROM_DIRECTORIES(ZZZ_MANIPULATE_FILES_SOURCES ZZZ_MANIPULATE_FILES_SOURCE_DIRECTORY_LIST)

PRINT_STATUS("Looking for TST directories in: [${ZZZ_MANIPULATE_FILES_TEST_DIRECTORY}]")
GET_SUB_DIRECTORY_LIST(ZZZ_MANIPULATE_FILES_TEST_DIRECTORY_LIST ${ZZZ_MANIPULATE_FILES_TEST_DIRECTORY})
GET_SOURCE_FILES_FROM_DIRECTORIES(ZZZ_MANIPULATE_FILES_TESTS ZZZ_MANIPULATE_FILES_TEST_DIRECTORY_LIST)

set(ZZZ_MANIPULATE_FILES_SOURCES_AND_TESTS
    ${ZZZ_MANIPULATE_FILES_SOURCES}
    ${ZZZ_MANIPULATE_FILES_TESTS}
)
