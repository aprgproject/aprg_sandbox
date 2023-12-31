set(FILE_DESTRUCTOR_SOURCE_DIRECTORY
    ${FILE_DESTRUCTOR_DIR}/src
)

set(FILE_DESTRUCTOR_TEST_DIRECTORY
    ${FILE_DESTRUCTOR_DIR}/tst
)

set(FILE_DESTRUCTOR_MAIN_DIRECTORY
    ${FILE_DESTRUCTOR_DIR}/main
)

set(FILE_DESTRUCTOR_INCLUDE_DIRECTORIES
    ${FILE_DESTRUCTOR_SOURCE_DIRECTORY}
)

set(FILE_DESTRUCTOR_TEST_INCLUDE_DIRECTORIES
    ${FILE_DESTRUCTOR_TEST_DIRECTORY}
)

PRINT_STATUS("Looking for SRC directories in: [${FILE_DESTRUCTOR_SOURCE_DIRECTORY}]")
GET_SUB_DIRECTORY_LIST(FILE_DESTRUCTOR_SOURCE_DIRECTORY_LIST ${FILE_DESTRUCTOR_SOURCE_DIRECTORY})
GET_SOURCE_FILES_FROM_DIRECTORIES(FILE_DESTRUCTOR_SOURCES FILE_DESTRUCTOR_SOURCE_DIRECTORY_LIST)

PRINT_STATUS("Looking for TST directories in: [${FILE_DESTRUCTOR_TEST_DIRECTORY}]")
GET_SUB_DIRECTORY_LIST(FILE_DESTRUCTOR_TEST_DIRECTORY_LIST ${FILE_DESTRUCTOR_TEST_DIRECTORY})
GET_SOURCE_FILES_FROM_DIRECTORIES(FILE_DESTRUCTOR_TESTS FILE_DESTRUCTOR_TEST_DIRECTORY_LIST)

PRINT_STATUS("Looking for MAIN directories in: [${FILE_DESTRUCTOR_MAIN_DIRECTORY}]")
GET_SUB_DIRECTORY_LIST(FILE_DESTRUCTOR_MAIN_DIRECTORY_LIST ${FILE_DESTRUCTOR_MAIN_DIRECTORY})
GET_SOURCE_FILES_FROM_DIRECTORIES(FILE_DESTRUCTOR_MAIN_SOURCES FILE_DESTRUCTOR_MAIN_DIRECTORY_LIST)

set(FILE_DESTRUCTOR_SOURCES_AND_TESTS
    ${FILE_DESTRUCTOR_SOURCES}
    ${FILE_DESTRUCTOR_TESTS}
)
