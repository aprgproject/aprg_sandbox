#Assign WcdmaToolsBackend directory, this needs aprg directory
set(WCDMA_TOOLS_BACKEND_DIR ${APRG_DIR}/WcdmaTools/WcdmaToolsBackend/)

#Include WCDMA_TOOLS_BACKEND files and directories
include(${WCDMA_TOOLS_BACKEND_DIR}/cmake/FilesAndDirectories.cmake)

include_directories(${WCDMA_TOOLS_BACKEND_INCLUDE_DIRECTORIES})
add_library(WCDMA_TOOLS_BACKEND ${WCDMA_TOOLS_BACKEND_SOURCES})
