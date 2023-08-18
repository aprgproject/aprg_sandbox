set(CODING_COMPETITIONS_COMMON_DIRECTORY
    ${APRG_DIR}/CodingCompetitions/Common
)
set(GOOGLE_KICK_START_TEST_DIRECTORY
    ${GOOGLE_KICK_START_DIR}/tst
    #for specific rounds only:    #${GOOGLE_KICK_START_DIR}/tst/2020/RoundH
)

set(GOOGLE_KICK_START_INCLUDE_DIRECTORIES
    ${CODING_COMPETITIONS_COMMON_DIRECTORY}
)

set(GOOGLE_KICK_START_TEST_INCLUDE_DIRECTORIES
    ${GOOGLE_KICK_START_TEST_DIRECTORY}
)

PRINT_STATUS("Looking for COMMON directories in: [${CODING_COMPETITIONS_COMMON_DIRECTORY}]")
GET_SUB_DIRECTORY_LIST(CODING_COMPETITIONS_COMMON_DIRECTORY_LIST ${CODING_COMPETITIONS_COMMON_DIRECTORY})
GET_SOURCE_FILES_FROM_DIRECTORIES(CODING_COMPETITIONS_SOURCES CODING_COMPETITIONS_COMMON_DIRECTORY_LIST)

PRINT_STATUS("Looking for TST directories in: [${GOOGLE_KICK_START_TEST_DIRECTORY}]")
GET_SUB_DIRECTORY_LIST(GOOGLE_KICK_START_TEST_DIRECTORY_LIST ${GOOGLE_KICK_START_TEST_DIRECTORY})
GET_SOURCE_FILES_FROM_DIRECTORIES(GOOGLE_KICK_START_TESTS GOOGLE_KICK_START_TEST_DIRECTORY_LIST)

set(GOOGLE_KICK_START_SOURCES_AND_TESTS
    ${CODING_COMPETITIONS_SOURCES}
    ${GOOGLE_KICK_START_TESTS}
)
