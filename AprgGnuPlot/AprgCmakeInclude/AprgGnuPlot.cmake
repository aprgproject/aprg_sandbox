#Assign AprgCommon directory, this needs aprg directory
set(APRG_GNU_PLOT_DIR ${APRG_DIR}/AprgGnuPlot/AprgGnuPlot/)

#Include APRG_COMMON files and directories
include(${APRG_GNU_PLOT_DIR}/cmake/FilesAndDirectories.cmake)

include_directories(${APRG_GNU_PLOT_INCLUDE_DIRECTORIES})
add_library(APRG_GNU_PLOT ${APRG_GNU_PLOT_SOURCES})
