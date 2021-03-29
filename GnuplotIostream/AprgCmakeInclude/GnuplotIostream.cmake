#Assign AprgCommon directory, this needs aprg directory
set(GNUPLOT_IOSTREAM_DIR ${APRG_DIR}/GnuplotIostream/GnuplotIostream/)

#Include APRG_COMMON files and directories
include(${GNUPLOT_IOSTREAM_DIR}/cmake/FilesAndDirectories.cmake)

include_directories(${GNUPLOT_IOSTREAM_INCLUDE_DIRECTORIES})
add_library(GNUPLOT_IOSTREAM ${GNUPLOT_IOSTREAM_SOURCES})
