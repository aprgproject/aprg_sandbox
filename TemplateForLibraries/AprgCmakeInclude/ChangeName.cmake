#Assign AprgCommon directory, this needs aprg directory
set(TEMPLATE_FOR_LIBRARIES_DIR ${APRG_DIR}/TemplateForLibraries/TemplateForLibraries/)

#Include APRG_COMMON files and directories
include(${TEMPLATE_FOR_LIBRARIES_DIR}/cmake/FilesAndDirectories.cmake)

include_directories(${TEMPLATE_FOR_LIBRARIES_INCLUDE_DIRECTORIES})
add_library(TEMPLATE_FOR_LIBRARIES ${TEMPLATE_FOR_LIBRARIES_SOURCES})
