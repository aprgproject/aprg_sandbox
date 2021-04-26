include(${APRG_DIR}/AprgCMakeHelpers/FileAndDirectoryMacros.cmake)
include(${APRG_DIR}/AprgCMakeHelpers/PrintMacros.cmake)

set(APRG_AUDIO_SOURCE_DIRECTORY
    ${APRG_AUDIO_DIR}/src
)

set(APRG_AUDIO_TEST_DIRECTORY
    ${APRG_AUDIO_DIR}/tst
)

set(APRG_AUDIO_MAIN_DIRECTORY
    ${APRG_AUDIO_DIR}/main
)

set(APRG_AUDIO_INCLUDE_DIRECTORIES
    ${APRG_AUDIO_SOURCE_DIRECTORY}
)

set(APRG_AUDIO_TEST_INCLUDE_DIRECTORIES
    ${APRG_AUDIO_TEST_DIRECTORY}
)

PRINT_STATUS("Looking for SRC directories in: [${APRG_AUDIO_SOURCE_DIRECTORY}]")
GET_SUB_DIRECTORY_LIST(APRG_AUDIO_SOURCE_DIRECTORY_LIST ${APRG_AUDIO_SOURCE_DIRECTORY})
GET_SOURCE_FILES_FROM_DIRECTORIES(APRG_AUDIO_SOURCES APRG_AUDIO_SOURCE_DIRECTORY_LIST)

PRINT_STATUS("Looking for TST directories in: [${APRG_AUDIO_TEST_DIRECTORY}]")
GET_SUB_DIRECTORY_LIST(APRG_AUDIO_TEST_DIRECTORY_LIST ${APRG_AUDIO_TEST_DIRECTORY})
GET_SOURCE_FILES_FROM_DIRECTORIES(APRG_AUDIO_TESTS APRG_AUDIO_TEST_DIRECTORY_LIST)

PRINT_STATUS("Looking for MAIN directories in: [${APRG_AUDIO_MAIN_DIRECTORY}]")
GET_SUB_DIRECTORY_LIST(APRG_AUDIO_MAIN_DIRECTORY_LIST ${APRG_AUDIO_MAIN_DIRECTORY})
GET_SOURCE_FILES_FROM_DIRECTORIES(APRG_AUDIO_MAIN_SOURCES APRG_AUDIO_MAIN_DIRECTORY_LIST)

set(APRG_AUDIO_SOURCES_AND_TESTS
    ${APRG_AUDIO_SOURCES}
    ${APRG_AUDIO_TESTS}
)