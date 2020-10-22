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
    src/UserInterface/UserInterface.cpp
    src/UserInterface/UserInterface.hpp
    src/main.cpp
    src/WebCrawler/CrawlConfiguration/CrawlConfiguration.cpp
    src/WebCrawler/CrawlConfiguration/CrawlConfiguration.hpp
    src/WebCrawler/Crawlers/ChiaAnimeCrawler.cpp
    src/WebCrawler/Crawlers/ChiaAnimeCrawler.hpp
    src/WebCrawler/Crawlers/DoujinMoeCrawler.cpp
    src/WebCrawler/Crawlers/DoujinMoeCrawler.hpp
    src/WebCrawler/Crawlers/Gehen.cpp
    src/WebCrawler/Crawlers/GuroManga.cpp
    src/WebCrawler/Crawlers/HBrowse.cpp
    src/WebCrawler/Crawlers/Hentai2Read.cpp
    src/WebCrawler/Crawlers/MangaFox.cpp
    src/WebCrawler/Crawlers/MangaHere.cpp
    src/WebCrawler/Crawlers/MangaPark.cpp
    src/WebCrawler/Crawlers/OneDownloadPerPageCrawler.cpp
    src/WebCrawler/Crawlers/OneDownloadPerPageCrawler.hpp
    src/WebCrawler/Crawlers/Y8Crawler.cpp
    src/WebCrawler/Crawlers/Y8Crawler.hpp
    src/WebCrawler/Crawlers/Youtube.cpp
    src/WebCrawler/Crawlers/Youtube.hpp
    src/WebCrawler/CrawlHelpers/AutomationHelper.cpp
    src/WebCrawler/CrawlHelpers/AutomationHelper.hpp
    src/WebCrawler/CrawlHelpers/Converters.cpp
    src/WebCrawler/CrawlHelpers/Downloaders.cpp
    src/WebCrawler/CrawlHelpers/Downloaders.hpp
    src/WebCrawler/CrawlMode.hpp
    src/WebCrawler/CrawlState.hpp
    src/WebCrawler/WebCrawler.cpp
    src/WebCrawler/WebCrawler.hpp
)

set(INCLUDE_DIRECTORIES
    src/
    src/UserInterface
    src/WebCrawler
)

set(CMAKE_FIND_LIBRARY_SUFFIXES ".a")
set(BUILD_SHARED_LIBRARIES OFF)
set(CMAKE_EXE_LINKER_FLAGS "-static")
add_executable(${OUTFILE} ${SOURCES})
include_directories(${INCLUDE_DIRECTORIES} ${GTEST_INCLUDE_DIRS})
target_link_libraries(${OUTFILE} ${CMAKE_THREAD_LIBS_INIT} APRG_COMMON CURL_CPP)
