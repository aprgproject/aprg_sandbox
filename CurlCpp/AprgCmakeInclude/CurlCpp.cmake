#Include curl library, this needs aprg directory
include(${APRG_DIR}/curl-7.38.0/AprgCmakeInclude/curl.cmake)

#Assign curlCpp directory, this needs aprg directory
set(CURL_CPP_DIR ${APRG_DIR}/CurlCpp/CurlCpp/)

#Include CURL_CPP_SOURCES
include(${CURL_CPP_DIR}/CMake/FilesAndDirectories.cmake)

include_directories(${CURL_CPP_INCLUDE_DIRECTORIES})
add_library(CURL_CPP ${CURL_CPP_SOURCES})
target_link_libraries(CURL_CPP CURL_LIB)
