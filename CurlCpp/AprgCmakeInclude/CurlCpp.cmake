#Include curl library, this needs aprg directory
include(${APRG_DIR}/curl-7.38.0/aprgCmakeInclude/curl.cmake)

#Assign curlCpp directory, needs aprg directory
set(CURL_CPP_DIR ${APRG_DIR}/CurlCpp/CurlCpp/)

#Include curl library
set(CURL_CPP_INCLUDE_DIRECTORIES
    ${CURL_CPP_DIR}/include
    ${CURL_CPP_DIR}
    ${CURL_CPP_DIR}/src
)

#Include CURL_CPP_SOURCES
include(${CURL_CPP_DIR}/cmake/CurlCppSources.cmake)

include_directories(${CURL_CPP_INCLUDE_DIRECTORIES})
add_library(CURL_CPP ${CURL_CPP_SOURCES})
target_link_libraries(CURL_CPP CURL_LIB)
