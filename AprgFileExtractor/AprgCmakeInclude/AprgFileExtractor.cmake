#Assign AprgFileExtractor directory, this needs aprg directory
set(APRG_FILE_EXTRACTOR_DIR ${APRG_DIR}/AprgFileExtractor/AprgFileExtractor/)

#Include APRG_FILE_EXTRACTOR_DIR files and directories
include(${APRG_FILE_EXTRACTOR_DIR}/cmake/FilesAndDirectories.cmake)

include_directories(${APRG_FILE_EXTRACTOR_INCLUDE_DIRECTORIES})
add_library(APRG_FILE_EXTRACTOR ${APRG_FILE_EXTRACTOR_SOURCES})
