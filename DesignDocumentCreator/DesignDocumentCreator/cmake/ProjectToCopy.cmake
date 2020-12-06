MACRO_GET_ALL_SOURCES(${DesignDocumentCreatorDirectory}/src/ProjectToCopy FEATURE_SOURCES)
MACRO_GET_ALL_SOURCES(${DesignDocumentCreatorDirectory}/tst/ProjectToCopy FEATURE_TESTS)
SET(FEATURE_INCLUDE_DIRECTORIES ${DesignDocumentCreatorDirectory}/src/ProjectToCopy ${DesignDocumentCreatorDirectory}/tst/ProjectToCopy)
add_definitions(-DLOG_LOCATION="${APRG_DIR}/DesignDocumentCreator/DesignDocumentCreatorLogs/ProjectToCopy")


