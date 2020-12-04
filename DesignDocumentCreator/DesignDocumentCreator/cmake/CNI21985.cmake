MACRO_GET_ALL_SOURCES(${DesignDocumentCreatorDirectory}/src/CNI21985 FEATURE_SOURCES)
MACRO_GET_ALL_SOURCES(${DesignDocumentCreatorDirectory}/tst/CNI21985 FEATURE_TESTS)
SET(FEATURE_INCLUDE_DIRECTORIES ${DesignDocumentCreatorDirectory}/src/CNI21985 ${DesignDocumentCreatorDirectory}/tst/CNI21985)
add_definitions(-DLOG_LOCATION="${APRG_DIR}/DesignDocumentCreator/DesignDocumentCreatorLogs/CNI21985")


