#include "AprgWebCrawler.hpp"

#include <AlbaFileReader.hpp>
#include <algorithm>
#include <fstream>
#include <iostream>

#define WEBVIEWERPATH R"(C:\APRG\WebViewerForDownload\WebViewerForDownload\WebViewerForDownload.exe)"

using namespace std;

namespace alba
{

AprgWebCrawler::AprgWebCrawler(string const& workingDirectory)
    : m_isModeRecognized(false)
{
    m_workingPathHandler.inputPath(workingDirectory);
    m_memoryCardPathHandler.inputPath(workingDirectory + R"(\MemoryCard.txt)");
    if (m_memoryCardPathHandler.isFoundInLocalSystem() && m_memoryCardPathHandler.isFile())
    {
        loadMemoryCard();
    }
}

bool AprgWebCrawler::isValid() const
{
    return m_workingPathHandler.isFoundInLocalSystem() &&
            m_workingPathHandler.isDirectory() &&
            m_memoryCardPathHandler.isFoundInLocalSystem() &&
            m_memoryCardPathHandler.isFile() &&
            m_isModeRecognized &&
            !isWebLinksEmpty() &&
            isWebLinksValid();
}

void AprgWebCrawler::printStatus() const
{
    if(!m_workingPathHandler.isFoundInLocalSystem())
    {
        cout << "Working directory: ["<< m_workingPathHandler.getFullPath() << "] is not found" << endl;
    }
    else if(!m_workingPathHandler.isDirectory())
    {
        cout << "Working directory: ["<< m_workingPathHandler.getFullPath() << "] is not a directory" << endl;
    }
    else if(!m_memoryCardPathHandler.isFoundInLocalSystem())
    {
        cout << "Memory card: ["<< m_workingPathHandler.getFullPath() << "] is not found" << endl;
    }
    else if(!m_memoryCardPathHandler.isFile())
    {
        cout << "Memory card: ["<< m_workingPathHandler.getFullPath() << "] is not a file" << endl;
    }
    else if(isWebLinksEmpty())
    {
        cout << "There are no web links in memory card" << endl;
    }
    else if(!isWebLinksValid())
    {
        cout << "Web links are not valid" << endl;
        for(string const& webLink : m_webLinks)
        {
            AlbaWebPathHandler webPathHandler;
            webPathHandler.inputPath(webLink);
            cout << "Url: ["<< webPathHandler.getFullPath() << "] isEmpty: " << webPathHandler.isEmpty() << " hasProtocol: " << webPathHandler.hasProtocol() << endl;
        }
    }
    else if(m_isModeRecognized)
    {
        cout << "Mode: ["<< getCrawlerModeString() << "] is not a recognized mode" << endl;
    }
    else
    {
        cout << "Status is okay" << endl;
    }
}

void AprgWebCrawler::saveMemoryCard() const
{
    ofstream memoryCardStream(m_memoryCardPathHandler.getFullPath());
    if(memoryCardStream.is_open())
    {
        memoryCardStream << getCrawlerModeString() << endl;
        for(string const& webLink : m_webLinks)
        {
            if(!webLink.empty())
            {
                memoryCardStream << webLink << endl;
            }
        }
    }
}

void AprgWebCrawler::loadMemoryCard()
{
    ifstream memoryCardStream(m_memoryCardPathHandler.getFullPath());
    if(memoryCardStream.is_open())
    {
        AlbaFileReader memoryCardReader(memoryCardStream);
        setCrawlerMode(memoryCardReader.getLineAndIgnoreWhiteSpaces());
        while(memoryCardReader.isNotFinished())
        {
            AlbaWebPathHandler webPathHandler;
            webPathHandler.inputPath(memoryCardReader.getLineAndIgnoreWhiteSpaces());
            if(!webPathHandler.isEmpty())
            {
                m_webLinks.push_back(webPathHandler.getFullPath());
            }
        }
    }
}

void AprgWebCrawler::crawl()
{
    switch(m_mode)
    {
    case CrawlerMode::ChiaAnime:
        crawlForChiaAnime();
        break;
    case CrawlerMode::Gehen:
    case CrawlerMode::GuroManga:
    case CrawlerMode::Mangafox:
    case CrawlerMode::MangafoxWithVolume:
    case CrawlerMode::Mangahere:
    case CrawlerMode::Y8:
        crawlOneHtmlAndOneFileToDownload();
        break;
    case CrawlerMode::Youtube:
        crawlForYoutube();
        break;
    }
}

void AprgWebCrawler::setCrawlerMode(string const& modeString)
{
    if("chiaanime" == modeString || "CrawlerMode::ChiaAnime" == modeString)
    {
        m_mode = CrawlerMode::ChiaAnime;
    }
    else if("gehen" == modeString || "CrawlerMode::Gehen" == modeString)
    {
        m_mode = CrawlerMode::Gehen;
    }
    else if("guromanga" == modeString || "CrawlerMode::GuroManga" == modeString)
    {
        m_mode = CrawlerMode::GuroManga;
    }
    else if("mangafox" == modeString || "CrawlerMode::Mangafox" == modeString)
    {
        m_mode = CrawlerMode::Mangafox;
    }
    else if("mangafoxfullpath" == modeString || "CrawlerMode::MangafoxWithVolume" == modeString)
    {
        m_mode = CrawlerMode::MangafoxWithVolume;
    }
    else if("mangahere" == modeString || "CrawlerMode::Mangahere" == modeString)
    {
        m_mode = CrawlerMode::Mangahere;
    }
    else if("y8" == modeString || "CrawlerMode::Y8" == modeString)
    {
        m_mode = CrawlerMode::Y8;
    }
    else if("youtube" == modeString || "CrawlerMode::Youtube" == modeString)
    {
        m_mode = CrawlerMode::Youtube;
    }
    else
    {
        cout << "AprgWebCrawler::setCrawlerMode | Mode is not recognized" << endl;
    }
}

#define GET_ENUM_STRING(en) \
    case en: \
    return #en;

string AprgWebCrawler::getCrawlerModeString() const
{
    switch(m_mode)
    {
    GET_ENUM_STRING(CrawlerMode::ChiaAnime)
            GET_ENUM_STRING(CrawlerMode::Gehen)
            GET_ENUM_STRING(CrawlerMode::GuroManga)
            GET_ENUM_STRING(CrawlerMode::Mangafox)
            GET_ENUM_STRING(CrawlerMode::MangafoxWithVolume)
            GET_ENUM_STRING(CrawlerMode::Mangahere)
            GET_ENUM_STRING(CrawlerMode::Y8)
            GET_ENUM_STRING(CrawlerMode::Youtube)
    }
    return "";
}

bool AprgWebCrawler::isWebLinksEmpty() const
{
    return m_webLinks.empty();
}

bool AprgWebCrawler::isWebLinksValid() const
{
    return all_of(m_webLinks.begin(), m_webLinks.end(), [](string const& webLink)
    {
        AlbaWebPathHandler webPathHandler;
        webPathHandler.inputPath(webLink);
        return !webPathHandler.isEmpty() && webPathHandler.hasProtocol();
    });
}

AlbaWebPathHandler AprgWebCrawler::getPathHandlerFromWebLinksInFront() const
{
    AlbaWebPathHandler webPathHandler;
    if(!isWebLinksEmpty())
    {
        webPathHandler.inputPath(m_webLinks.front());
    }
    return webPathHandler;
}

void AprgWebCrawler::saveAllLinksUsingWebViewerForDownload(AlbaWebPathHandler const& webPathHandler, AlbaWindowsPathHandler localHtmlPathHandler) const
{
    localHtmlPathHandler.deleteFile();
    string webViewerCommand(string(WEBVIEWERPATH)+R"( ")"+webPathHandler.getFullPath()+R"(" ")"+localHtmlPathHandler.getFullPath()+R"(")");
    cout << webViewerCommand << endl;
    system(webViewerCommand.c_str());
}

}
