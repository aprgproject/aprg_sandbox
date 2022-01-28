include(${APRG_DIR}/AprgCMakeHelpers/FileAndDirectoryMacros.cmake)
include(${APRG_DIR}/AprgCMakeHelpers/PrintMacros.cmake)

set(APRG_GREP_STRING_EVALUATOR_SOURCE_DIRECTORY
    ${APRG_GREP_STRING_EVALUATOR_DIR}/src
)

set(APRG_GREP_STRING_EVALUATOR_TEST_DIRECTORY
    ${APRG_GREP_STRING_EVALUATOR_DIR}/tst
)

set(APRG_GREP_STRING_EVALUATOR_INCLUDE_DIRECTORIES
    ${APRG_GREP_STRING_EVALUATOR_SOURCE_DIRECTORY}
)

set(APRG_GREP_STRING_EVALUATOR_TEST_INCLUDE_DIRECTORIES
    ${APRG_GREP_STRING_EVALUATOR_TEST_DIRECTORY}
)

PRINT_STATUS("Looking for SRC directories in: [${APRG_GREP_STRING_EVALUATOR_SOURCE_DIRECTORY}]")
GET_SUB_DIRECTORY_LIST(APRG_GREP_STRING_EVALUATOR_SOURCE_DIRECTORY_LIST ${APRG_GREP_STRING_EVALUATOR_SOURCE_DIRECTORY})
GET_SOURCE_FILES_FROM_DIRECTORIES(APRG_GREP_STRING_EVALUATOR_SOURCES APRG_GREP_STRING_EVALUATOR_SOURCE_DIRECTORY_LIST)

PRINT_STATUS("Looking for TST directories in: [${APRG_GREP_STRING_EVALUATOR_TEST_DIRECTORY}]")
GET_SUB_DIRECTORY_LIST(APRG_GREP_STRING_EVALUATOR_TEST_DIRECTORY_LIST ${APRG_GREP_STRING_EVALUATOR_TEST_DIRECTORY})
GET_SOURCE_FILES_FROM_DIRECTORIES(APRG_GREP_STRING_EVALUATOR_TESTS APRG_GREP_STRING_EVALUATOR_TEST_DIRECTORY_LIST)

set(APRG_GREP_STRING_EVALUATOR_SOURCES_AND_TESTS
    ${APRG_GREP_STRING_EVALUATOR_SOURCES}
    ${APRG_GREP_STRING_EVALUATOR_TESTS}
)