#Assign AprgCommon directory, this needs aprg directory
set(APRG_GREP_STRING_EVALUATOR_DIR ${APRG_DIR}/AprgGrepStringEvaluator/AprgGrepStringEvaluator/)

#Include APRG_COMMON files and directories
include(${APRG_GREP_STRING_EVALUATOR_DIR}/cmake/FilesAndDirectories.cmake)

include_directories(${APRG_GREP_STRING_EVALUATOR_INCLUDE_DIRECTORIES})
add_library(APRG_GREP_STRING_EVALUATOR ${APRG_GREP_STRING_EVALUATOR_SOURCES})
