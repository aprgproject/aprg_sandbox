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

#Include curlCpp, this needs APRG Directory
include(${APRG_DIR}/CurlCpp/AprgCmakeInclude/CurlCpp.cmake)

set(SOURCES
    src/DirectoryAndFileCorrector/DirectoryAndFileCorrector.cpp
    src/DirectoryAndFileCorrector/DirectoryAndFileCorrector.hpp
    src/DirectoryAndFileCorrector/DirectoryAndFileCorrector.cpp
    src/UserInterface/UserInterface.cpp
    src/UserInterface/UserInterface.hpp
    src/main.cpp
    src/WebCrawler/CrawlConfiguration/CrawlConfiguration.cpp
    src/WebCrawler/CrawlConfiguration/CrawlConfiguration.hpp
    src/WebCrawler/CrawlHelpers/ChiaAnime.cpp
    src/WebCrawler/CrawlHelpers/DownloadHelpers.cpp
    src/WebCrawler/CrawlHelpers/Gehen.cpp
    src/WebCrawler/CrawlHelpers/GoogleImages.cpp
    src/WebCrawler/CrawlHelpers/GuroManga.cpp
    src/WebCrawler/CrawlHelpers/HBrowse.cpp
    src/WebCrawler/CrawlHelpers/Hentai2Read.cpp
    src/WebCrawler/CrawlHelpers/MangaFox.cpp
    src/WebCrawler/CrawlHelpers/MangaHere.cpp
    src/WebCrawler/CrawlHelpers/MangaPark.cpp
    src/WebCrawler/CrawlHelpers/SharedCrawlers.cpp
    src/WebCrawler/CrawlHelpers/Youtube.cpp
    src/WebCrawler/CrawlHelpers/Y8.cpp
    src/WebCrawler/CrawlMode.hpp
    src/WebCrawler/CrawlState.hpp
    src/WebCrawler/LinksStructures/LinksForChiaAnime.cpp
    src/WebCrawler/LinksStructures/LinksForChiaAnime.hpp
    src/WebCrawler/LinksStructures/LinksForHtmlAndFileToDownload.cpp
    src/WebCrawler/LinksStructures/LinksForHtmlAndFileToDownload.hpp
    src/WebCrawler/LinksStructures/LinksForYoutube.cpp
    src/WebCrawler/LinksStructures/LinksForYoutube.hpp
    src/WebCrawler/WebCrawler.cpp
    src/WebCrawler/WebCrawler.hpp
)

set(INCLUDE_DIRECTORIES
    src/
    src/DirectoryAndFileCorrector
    src/UserInterface
    src/WebCrawler
)

set(CMAKE_FIND_LIBRARY_SUFFIXES ".a")
set(BUILD_SHARED_LIBRARIES OFF)
set(CMAKE_EXE_LINKER_FLAGS "-static")
add_executable(${OUTFILE} ${SOURCES})
include_directories(${INCLUDE_DIRECTORIES} ${GTEST_INCLUDE_DIRS})
target_link_libraries(${OUTFILE} ${CMAKE_THREAD_LIBS_INIT} APRG_COMMON CURL_CPP )
