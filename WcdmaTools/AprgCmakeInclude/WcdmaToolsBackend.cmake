#Assign WcdmaToolsBackend directory, this needs aprg directory
set(TCOM_TOOLS_BACKEND_DIR ${APRG_DIR}/WcdmaTools/WcdmaToolsBackend/)

#Include TCOM_TOOLS_BACKEND files and directories
include(${TCOM_TOOLS_BACKEND_DIR}/cmake/FilesAndDirectories.cmake)

include_directories(${TCOM_TOOLS_BACKEND_INCLUDE_DIRECTORIES})
add_library(TCOM_TOOLS_BACKEND ${TCOM_TOOLS_BACKEND_SOURCES})
