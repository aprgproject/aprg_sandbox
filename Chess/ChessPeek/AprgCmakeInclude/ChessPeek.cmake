#Assign AprgCommon directory, this needs aprg directory
set(CHESS_PEEK_DIR ${APRG_DIR}/ChessPeek/ChessPeek/)

#Include APRG_COMMON files and directories
include(${CHESS_PEEK_DIR}/cmake/FilesAndDirectories.cmake)

include_directories(${CHESS_PEEK_INCLUDE_DIRECTORIES})
add_library(CHESS_PEEK ${CHESS_PEEK_SOURCES})
