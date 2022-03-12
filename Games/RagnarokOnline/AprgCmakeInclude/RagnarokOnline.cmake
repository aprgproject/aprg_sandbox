#Assign AprgCommon directory, this needs aprg directory
set(RAGNAROK_ONLINE_DIR ${APRG_DIR}/RagnarokOnline/RagnarokOnline/)

#Include APRG_COMMON files and directories
include(${RAGNAROK_ONLINE_DIR}/cmake/FilesAndDirectories.cmake)

include_directories(${RAGNAROK_ONLINE_INCLUDE_DIRECTORIES})
add_library(RAGNAROK_ONLINE ${RAGNAROK_ONLINE_SOURCES})
