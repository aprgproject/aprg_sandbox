set(BTS_TRACE_DECODER_SOURCE_DIRECTORY
    ${BTS_TRACE_DECODER_DIR}/src
)
set(BTS_TRACE_DECODER_TEST_DIRECTORY
    ${BTS_TRACE_DECODER_DIR}/tst
)
set(BTS_TRACE_DECODER_MAIN_DIRECTORY
    ${BTS_TRACE_DECODER_DIR}/main
)

set(BTS_TRACE_DECODER_INCLUDE_DIRECTORIES
    ${BTS_TRACE_DECODER_SOURCE_DIRECTORY}
)

set(BTS_TRACE_DECODER_TEST_INCLUDE_DIRECTORIES
    ${BTS_TRACE_DECODER_TEST_DIRECTORY}
)

PRINT_STATUS("Looking for SRC directories in: [${BTS_TRACE_DECODER_SOURCE_DIRECTORY}]")
GET_SUB_DIRECTORY_LIST(BTS_TRACE_DECODER_SOURCE_DIRECTORY_LIST ${BTS_TRACE_DECODER_SOURCE_DIRECTORY})
GET_SOURCE_FILES_FROM_DIRECTORIES(BTS_TRACE_DECODER_SOURCES BTS_TRACE_DECODER_SOURCE_DIRECTORY_LIST)

PRINT_STATUS("Looking for TST directories in: [${BTS_TRACE_DECODER_TEST_DIRECTORY}]")
GET_SUB_DIRECTORY_LIST(BTS_TRACE_DECODER_TEST_DIRECTORY_LIST ${BTS_TRACE_DECODER_TEST_DIRECTORY})
GET_SOURCE_FILES_FROM_DIRECTORIES(BTS_TRACE_DECODER_TESTS BTS_TRACE_DECODER_TEST_DIRECTORY_LIST)

PRINT_STATUS("Looking for MAIN directories in: [${BTS_TRACE_DECODER_MAIN_DIRECTORY}]")
GET_SUB_DIRECTORY_LIST(BTS_TRACE_DECODER_MAIN_DIRECTORY_LIST ${BTS_TRACE_DECODER_MAIN_DIRECTORY})
GET_SOURCE_FILES_FROM_DIRECTORIES(BTS_TRACE_DECODER_MAIN_SOURCES BTS_TRACE_DECODER_MAIN_DIRECTORY_LIST)

set(BTS_TRACE_DECODER_SOURCES_AND_TESTS
    ${BTS_TRACE_DECODER_SOURCES}
    ${BTS_TRACE_DECODER_TESTS}
)
