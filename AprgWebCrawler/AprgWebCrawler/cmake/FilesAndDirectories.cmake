set(APRG_WEB_CRAWLER_SOURCE_DIRECTORY
    ${APRG_WEB_CRAWLER_DIR}/src
)
set(APRG_WEB_CRAWLER_INCLUDE_DIRECTORIES
    ${APRG_WEB_CRAWLER_SOURCE_DIRECTORY}
)

PRINT_STATUS("Looking for SRC directories in: [${APRG_WEB_CRAWLER_SOURCE_DIRECTORY}]")
GET_SUB_DIRECTORY_LIST(APRG_WEB_CRAWLER_SOURCE_DIRECTORY_LIST ${APRG_WEB_CRAWLER_SOURCE_DIRECTORY})
GET_SOURCE_FILES_FROM_DIRECTORIES(APRG_WEB_CRAWLER_SOURCES APRG_WEB_CRAWLER_SOURCE_DIRECTORY_LIST)
