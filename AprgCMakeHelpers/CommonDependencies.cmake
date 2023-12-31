if(WIN32)
    if (CMAKE_CXX_COMPILER_ID MATCHES "Clang|GNU")
        set(APRG_GTEST_DEPENDENCIES gtest ${CMAKE_THREAD_LIBS_INIT})
    elseif (CMAKE_CXX_COMPILER_ID STREQUAL "MSVC")
        set(APRG_GTEST_DEPENDENCIES gtest)
    endif()
elseif(APPLE)
    set(APRG_GTEST_DEPENDENCIES gtest ${CMAKE_THREAD_LIBS_INIT} pthread)
elseif(UNIX)
    set(APRG_GTEST_DEPENDENCIES gtest ${CMAKE_THREAD_LIBS_INIT} pthread)
endif()

if(WIN32)
    if (CMAKE_CXX_COMPILER_ID MATCHES "Clang|GNU")
        set(APRG_SHLWAPI_DEPENDENCIES -lshlwapi)
    elseif (CMAKE_CXX_COMPILER_ID STREQUAL "MSVC")
        set(APRG_SHLWAPI_DEPENDENCIES shlwapi.lib)
    endif()
endif()

if(WIN32)
    if (CMAKE_CXX_COMPILER_ID MATCHES "Clang|GNU")
        set(APRG_ICONV_DEPENDENCIES iconv)
    elseif (CMAKE_CXX_COMPILER_ID STREQUAL "MSVC")
        include(FindIconv)
        set(APRG_ICONV_DEPENDENCIES iconv)
    endif()
endif()
