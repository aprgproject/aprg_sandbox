MACRO_GET_ALL_SOURCES(${DesignDocumentCreatorDirectory}/src/CNI21985 CNI21985_FEATURE_SOURCES)
MACRO_GET_ALL_SOURCES(${DesignDocumentCreatorDirectory}/tst/CNI21985 CNI21985_FEATURE_TESTS)
SET(CNI21985_FEATURE_INCLUDE_DIRECTORIES ${DesignDocumentCreatorDirectory}/src/CNI21985 ${DesignDocumentCreatorDirectory}/tst/CNI21985)
SET(FEATURE_SOURCES ${FEATURE_SOURCES} ${CNI21985_FEATURE_SOURCES})
SET(FEATURE_TESTS ${FEATURE_TESTS} ${CNI21985_FEATURE_TESTS})
SET(FEATURE_INCLUDE_DIRECTORIES ${FEATURE_INCLUDE_DIRECTORIES} ${CNI21985_FEATURE_INCLUDE_DIRECTORIES})
