#Assign AprgCommon directory, this needs aprg directory
set(TEMPLATE_FOR_ALL_CASES_DIR ${APRG_DIR}/TemplateForAllCases/TemplateForAllCases/)

#Include APRG_COMMON files and directories
include(${TEMPLATE_FOR_ALL_CASES_DIR}/cmake/FilesAndDirectories.cmake)

include_directories(${TEMPLATE_FOR_ALL_CASES_INCLUDE_DIRECTORIES})
add_library(TEMPLATE_FOR_ALL_CASES ${TEMPLATE_FOR_ALL_CASES_SOURCES})
