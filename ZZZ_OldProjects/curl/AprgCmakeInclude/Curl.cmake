#Assign CURL_DIR directory, this needs aprg directory
set(CURL_DIR ${APRG_DIR}/CURL/)

if(WIN32)
    #Include CURL files and directories
    set(CURL_INCLUDE_DIRECTORIES ${CURL_DIR}/include/curl-7.79/)

    include_directories(${CURL_INCLUDE_DIRECTORIES})

    # add libraries
    add_library(CURL SHARED IMPORTED)
    set_property(TARGET CURL PROPERTY IMPORTED_IMPLIB ${CURL_DIR}/lib/curl-7.79/libcurl.a)
    add_library(CURL_DLL SHARED IMPORTED)
    set_property(TARGET CURL_DLL PROPERTY IMPORTED_IMPLIB ${CURL_DIR}/lib/curl-7.79/libcurl.dll.a)
    set (CURL_LIBRARIES_TO_LINK CURL CURL_DLL)
else()
    find_package(CURL REQUIRED)
    set (CURL_LIBRARIES_TO_LINK CURL::CURL)
endif()
