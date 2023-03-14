#Include curl library, this needs aprg directory
include(${APRG_DIR}/curl/AprgCmakeInclude/Curl.cmake)

#Assign CurlCpp directory, this needs aprg directory
set(APRG_CURL_CPP_DIR ${APRG_DIR}/CurlCpp/CurlCpp/)

#Include APRG_CURL_CPP files and directories
include(${APRG_CURL_CPP_DIR}/cmake/FilesAndDirectories.cmake)

include_directories(${APRG_CURL_CPP_INCLUDE_DIRECTORIES})
add_library(APRG_CURL_CPP ${APRG_CURL_CPP_SOURCES})
target_link_libraries(APRG_CURL_CPP ${CURL_LIBRARIES_TO_LINK})