#Assign AprgCommon directory, this needs aprg directory
set(BOOST_DIR ${APRG_DIR}/Boost/Boost/)

#Include APRG_COMMON files and directories
include(${BOOST_DIR}/cmake/FilesAndDirectories.cmake)

include_directories(${BOOST_INCLUDE_DIRECTORIES})
add_library(BOOST ${BOOST_SOURCES})
