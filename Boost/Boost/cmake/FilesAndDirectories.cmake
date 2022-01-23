include(${APRG_DIR}/AprgCMakeHelpers/FileAndDirectoryMacros.cmake)
include(${APRG_DIR}/AprgCMakeHelpers/PrintMacros.cmake)

set(BOOST_TEST_DIRECTORY
    ${BOOST_DIR}/tst
)

set(BOOST_TEST_INCLUDE_DIRECTORIES
    ${BOOST_TEST_DIRECTORY}
)

PRINT_STATUS("Looking for TST directories in: [${BOOST_TEST_DIRECTORY}]")
GET_SUB_DIRECTORY_LIST(BOOST_TEST_DIRECTORY_LIST ${BOOST_TEST_DIRECTORY})
GET_SOURCE_FILES_FROM_DIRECTORIES(BOOST_TESTS BOOST_TEST_DIRECTORY_LIST)

include(${BOOST_DIR}/cmake/IncludeBoost.cmake)