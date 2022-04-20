#Assign AprgCommon directory, this needs aprg directory
set(CHESS_UTILITIES_DIR ${APRG_DIR}/Chess/ChessUtilities/ChessUtilities/)

#Include APRG_COMMON files and directories
include(${CHESS_UTILITIES_DIR}/cmake/FilesAndDirectories.cmake)
include_directories(${CHESS_UTILITIES_INCLUDE_DIRECTORIES})
add_library(CHESS_UTILITIES ${CHESS_UTILITIES_SOURCES})