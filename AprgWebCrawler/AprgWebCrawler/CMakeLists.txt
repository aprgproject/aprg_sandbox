cmake_minimum_required(VERSION 2.8)
project(AprgWebCrawler C CXX)

set(OUTFILE ${PROJECT_NAME})

#Assign APRG Directory
set(APRG_DIR ${CMAKE_CURRENT_SOURCE_DIR}/../../)

#Assign Flags do not include -mwindows to make a console build
set(CMAKE_C_FLAGS "-Wall -Wextra -pedantic --coverage -std=c99")
set(CMAKE_CXX_FLAGS "-Wall -Wextra -pedantic --coverage -std=c++11")

#Include aprgCommon, this needs APRG Directory
include(${APRG_DIR}/AprgCommon/AprgCmakeInclude/AprgCommon.cmake)

#Include gTest, this needs APRG Directory
include(${APRG_DIR}/gtest-1.7.0/AprgCmakeInclude/gtest.cmake)

#Include curlCpp, this needs APRG Directory
include(${APRG_DIR}/CurlCpp/AprgCmakeInclude/CurlCpp.cmake)

set(SOURCES
    src/AprgWebCrawler.cpp
    src/AprgWebCrawler.hpp
    src/CrawlHelpers/ChiaAnime.cpp
    src/CrawlHelpers/Gehen.cpp
    src/CrawlHelpers/GoogleImages.cpp
    src/CrawlHelpers/GuroManga.cpp
    src/CrawlHelpers/MangaFox.cpp
    src/CrawlHelpers/MangaHere.cpp
    src/CrawlHelpers/SharedCrawlers.cpp
    src/CrawlHelpers/Youtube.cpp
    src/CrawlHelpers/Y8.cpp
    src/LinksStructures/LinksStructures.cpp
    src/LinksStructures/LinksStructures.hpp
    src/main.cpp
)

add_executable(${OUTFILE} ${SOURCES})
include_directories(src ${GTEST_INCLUDE_DIRS})
target_link_libraries(${OUTFILE} gtest ${CMAKE_THREAD_LIBS_INIT} APRG_COMMON CURL_CPP )
add_test(${OUTFILE} ${OUTFILE})
