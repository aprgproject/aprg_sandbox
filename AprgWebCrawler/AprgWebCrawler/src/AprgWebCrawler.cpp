#include "AprgWebCrawler.hpp"

#include <AlbaFileReader.hpp>
#include <algorithm>
#include <fstream>
#include <iostream>

#define FIREFOX_EXECUTABLE_PATH R"(C:\"Program Files"\"Mozilla Firefox"\firefox.exe)"

using namespace std;

namespace alba
{

AprgWebCrawler::AprgWebCrawler(string const& workingDirectory)
    : m_workingPathHandler(workingDirectory)
    , m_memoryCardPathHandler(workingDirectory + R"(\MemoryCard.txt)")
    , m_isModeRecognized(false)
{
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
            AlbaWebPathHandler webPathHandler(webLink);
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
            AlbaWebPathHandler webPathHandler(memoryCardReader.getLineAndIgnoreWhiteSpaces());
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
    case CrawlMode::ChiaAnime:
        crawlForChiaAnime();
        break;
    case CrawlMode::Gehen:
    case CrawlMode::GuroManga:
    case CrawlMode::HBrowse:
    case CrawlMode::Hentai2Read:
    case CrawlMode::Mangafox:
    case CrawlMode::MangafoxWithVolume:
    case CrawlMode::Mangahere:
    case CrawlMode::MangaPark:
    case CrawlMode::Y8:
        crawlOneHtmlAndOneFileToDownload();
        break;
    case CrawlMode::Youtube:
        crawlForYoutube();
        break;
    }}

void AprgWebCrawler::setCrawlerMode(string const& modeString)
{
    if("chiaanime" == modeString || "CrawlerMode::ChiaAnime" == modeString || "CrawlMode::ChiaAnime" == modeString)
    {
        m_mode = CrawlMode::ChiaAnime;
    }
    else if("gehen" == modeString || "CrawlerMode::Gehen" == modeString || "CrawlMode::Gehen" == modeString)
    {
        m_mode = CrawlMode::Gehen;
    }
    else if("guromanga" == modeString || "CrawlerMode::GuroManga" == modeString || "CrawlMode::GuroManga" == modeString)
    {
        m_mode = CrawlMode::GuroManga;
    }
    else if("hbrowse" == modeString || "CrawlerMode::HBrowse" == modeString || "CrawlMode::HBrowse" == modeString)
    {
        m_mode = CrawlMode::HBrowse;
    }
    else if("hentai2read" == modeString || "CrawlerMode::Hentai2Read" == modeString || "CrawlMode::Hentai2Read" == modeString)
    {
        m_mode = CrawlMode::Hentai2Read;
    }
    else if("mangafox" == modeString || "CrawlerMode::Mangafox" == modeString || "CrawlMode::Mangafox" == modeString)
    {
        m_mode = CrawlMode::Mangafox;
    }
    else if("mangafoxfullpath" == modeString || "CrawlerMode::MangafoxWithVolume" == modeString || "CrawlMode::MangafoxWithVolume" == modeString)
    {
        m_mode = CrawlMode::MangafoxWithVolume;
    }
    else if("mangahere" == modeString || "CrawlerMode::Mangahere" == modeString || "CrawlMode::Mangahere" == modeString)
    {
        m_mode = CrawlMode::Mangahere;
    }
    else if("mangapark" == modeString || "CrawlerMode::MangaPark" == modeString || "CrawlMode::MangaPark" == modeString)
    {
        m_mode = CrawlMode::MangaPark;
    }
    else if("y8" == modeString || "CrawlerMode::Y8" == modeString || "CrawlMode::Y8" == modeString)
    {
        m_mode = CrawlMode::Y8;
    }
    else if("youtube" == modeString || "CrawlerMode::Youtube" == modeString || "CrawlMode::Youtube" == modeString)
    {
        m_mode = CrawlMode::Youtube;
    }    else
    {        cout << "AprgWebCrawler::setCrawlerMode | Mode is not recognized" << endl;
    }
}#define GET_ENUM_STRING(en) \
    case en: \
    return #en;

string AprgWebCrawler::getCrawlerModeString() const
{
    switch(m_mode)
    {
    GET_ENUM_STRING(CrawlMode::ChiaAnime)
            GET_ENUM_STRING(CrawlMode::Gehen)
            GET_ENUM_STRING(CrawlMode::GuroManga)
            GET_ENUM_STRING(CrawlMode::HBrowse)
            GET_ENUM_STRING(CrawlMode::Hentai2Read)
            GET_ENUM_STRING(CrawlMode::Mangafox)
            GET_ENUM_STRING(CrawlMode::MangafoxWithVolume)
            GET_ENUM_STRING(CrawlMode::Mangahere)
            GET_ENUM_STRING(CrawlMode::MangaPark)
            GET_ENUM_STRING(CrawlMode::Y8)
            GET_ENUM_STRING(CrawlMode::Youtube)
    }
    return "";
}
bool AprgWebCrawler::isWebLinksEmpty() const
{
    return m_webLinks.empty();}

bool AprgWebCrawler::isWebLinksValid() const
{
    return all_of(m_webLinks.begin(), m_webLinks.end(), [](string const& webLink)
    {
        AlbaWebPathHandler webPathHandler(webLink);
        return !webPathHandler.isEmpty() && webPathHandler.hasProtocol();
    });
}

string AprgWebCrawler::getUserInputAfterManuallyUsingMozillaFirefox(AlbaWebPathHandler const& webPathHandler) const
{
    constexpr int bufferSize = 1000;
    char buffer[bufferSize];
    gotoLinkManuallyUsingMozillaFirefox(webPathHandler);
    cout<<"Enter user input:"<<endl;
    cin.getline(buffer, bufferSize);
    return string(buffer);
}

void AprgWebCrawler::gotoLinkManuallyUsingMozillaFirefox(AlbaWebPathHandler const& webPathHandler) const
{
    string firefoxCommand(string(FIREFOX_EXECUTABLE_PATH)+R"( ")"+webPathHandler.getFullPath()+R"(")");
    cout << firefoxCommand << endl;
    system(firefoxCommand.c_str());
}

}
