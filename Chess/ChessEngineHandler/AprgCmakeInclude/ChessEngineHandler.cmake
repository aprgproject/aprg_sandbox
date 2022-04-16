#Assign AprgCommon directory, this needs aprg directory
set(CHESS_ENGINE_HANDLER_DIR ${APRG_DIR}/ChessEngineHandler/ChessEngineHandler/)

#Include APRG_COMMON files and directories
include(${CHESS_ENGINE_HANDLER_DIR}/cmake/FilesAndDirectories.cmake)

include_directories(${CHESS_ENGINE_HANDLER_INCLUDE_DIRECTORIES})
add_library(CHESS_ENGINE_HANDLER ${CHESS_ENGINE_HANDLER_SOURCES})
