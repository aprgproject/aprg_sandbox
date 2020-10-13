#include "WebCrawler.hpp"

#include <AlbaFileReader.hpp>
#include <algorithm>#include <CurlInterface.hpp>
#include <fstream>
#include <iostream>

#define FIREFOX_EXECUTABLE_PATH R"(C:\"Program Files"\"Mozilla Firefox"\firefox.exe)"

using namespace curl::CurlInterface;
using namespace std;

namespace alba
{

WebCrawler::WebCrawler(string const& workingDirectory)
    : m_workingPathHandler(workingDirectory)
    , m_memoryCardPathHandler(workingDirectory + R"(\MemoryCard.txt)")
    , m_isModeRecognized(false)    , m_mode(CrawlMode::Empty)
    , m_state(CrawlState::Empty)
{
    if (m_memoryCardPathHandler.isFoundInLocalSystem() && m_memoryCardPathHandler.isFile())
    {
        loadMemoryCard();
    }
}

bool WebCrawler::isValid() const
{
    return m_workingPathHandler.isFoundInLocalSystem() &&
            m_workingPathHandler.isDirectory() &&            m_memoryCardPathHandler.isFoundInLocalSystem() &&
            m_memoryCardPathHandler.isFile() &&
            m_isModeRecognized &&
            !isWebLinksEmpty() &&
            isWebLinksValid();
}

void WebCrawler::printStatus() const
{
    if(!m_workingPathHandler.isFoundInLocalSystem())
    {        cout << "Working directory: ["<< m_workingPathHandler.getFullPath() << "] is not found" << endl;
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
        cout << "Mode: ["<< getCrawlerMode() << "] is not a recognized mode" << endl;
    }
    else
    {
        cout << "Status is okay" << endl;
    }
}

void WebCrawler::saveMemoryCard() const
{
    ofstream memoryCardStream(m_memoryCardPathHandler.getFullPath());
    if(memoryCardStream.is_open())    {
        memoryCardStream << getCrawlerMode() << endl;
        memoryCardStream << getCrawlerState() << endl;
        for(string const& webLink : m_webLinks)
        {
            if(!webLink.empty())
            {
                memoryCardStream << webLink << endl;
            }
        }
    }
}

void WebCrawler::loadMemoryCard()
{
    ifstream memoryCardStream(m_memoryCardPathHandler.getFullPath());
    if(memoryCardStream.is_open())    {
        AlbaFileReader memoryCardReader(memoryCardStream);
        while(memoryCardReader.isNotFinished())
        {
            string lineFromMemoryCard(memoryCardReader.getLineAndIgnoreWhiteSpaces());
            CrawlMode possibleMode(convertStringToCrawlerMode(lineFromMemoryCard));
            CrawlState possibleState(convertStringToCrawlerState(lineFromMemoryCard));
            AlbaWebPathHandler webPathHandler(lineFromMemoryCard);
            if(CrawlMode::Empty != possibleMode)
            {
                setCrawlerMode(possibleMode);
            }
            else if(CrawlState::Empty != possibleState)
            {
                setCrawlerState(possibleState);
            }
            else if(!webPathHandler.isEmpty())
            {
                m_webLinks.push_back(webPathHandler.getFullPath());
            }
        }
    }
}

void WebCrawler::crawl()
{
    switch(m_mode)
    {    case CrawlMode::ChiaAnime:
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
    case CrawlMode::Empty:
        cout<<"WebCrawler::crawl | CrawlMode is still not set."<<endl;
        break;
    }
}

void WebCrawler::setCrawlerMode(CrawlMode mode)
{
    m_mode = mode;
}

void WebCrawler::setCrawlerState(CrawlState state)
{
    m_state = state;
}

void WebCrawler::saveInvalidStateToMemoryCard(CrawlState state)
{
    setCrawlerState(state);
    saveMemoryCard();}

#define GET_ENUM_STRING(en) \
    case en: \
    return #en;

string WebCrawler::getCrawlerMode() const
{
    switch(m_mode)
    {    GET_ENUM_STRING(CrawlMode::Empty)
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

string WebCrawler::getCrawlerState() const
{
    switch(m_state)
    {    GET_ENUM_STRING(CrawlState::Empty)
            GET_ENUM_STRING(CrawlState::Active)
            GET_ENUM_STRING(CrawlState::DownloadedFileIsInvalid)
            GET_ENUM_STRING(CrawlState::LinksAreInvalid)
            GET_ENUM_STRING(CrawlState::NextLinkIsInvalid)
    }
    return "";
}

CrawlMode WebCrawler::convertStringToCrawlerMode(string const& modeString) const
{
    CrawlMode mode(CrawlMode::Empty);
    if("chiaanime" == modeString || "CrawlerMode::ChiaAnime" == modeString || "CrawlMode::ChiaAnime" == modeString)    {
        mode = CrawlMode::ChiaAnime;
    }
    else if("gehen" == modeString || "CrawlerMode::Gehen" == modeString || "CrawlMode::Gehen" == modeString)
    {
        mode = CrawlMode::Gehen;
    }
    else if("guromanga" == modeString || "CrawlerMode::GuroManga" == modeString || "CrawlMode::GuroManga" == modeString)
    {
        mode = CrawlMode::GuroManga;
    }
    else if("hbrowse" == modeString || "CrawlerMode::HBrowse" == modeString || "CrawlMode::HBrowse" == modeString)
    {
        mode = CrawlMode::HBrowse;
    }
    else if("hentai2read" == modeString || "CrawlerMode::Hentai2Read" == modeString || "CrawlMode::Hentai2Read" == modeString)
    {
        mode = CrawlMode::Hentai2Read;
    }
    else if("mangafox" == modeString || "CrawlerMode::Mangafox" == modeString || "CrawlMode::Mangafox" == modeString)
    {
        mode = CrawlMode::Mangafox;
    }
    else if("mangafoxfullpath" == modeString || "CrawlerMode::MangafoxWithVolume" == modeString || "CrawlMode::MangafoxWithVolume" == modeString)
    {
        mode = CrawlMode::MangafoxWithVolume;
    }
    else if("mangahere" == modeString || "CrawlerMode::Mangahere" == modeString || "CrawlMode::Mangahere" == modeString)
    {
        mode = CrawlMode::Mangahere;
    }
    else if("mangapark" == modeString || "CrawlerMode::MangaPark" == modeString || "CrawlMode::MangaPark" == modeString)
    {
        mode = CrawlMode::MangaPark;
    }
    else if("y8" == modeString || "CrawlerMode::Y8" == modeString || "CrawlMode::Y8" == modeString)
    {
        mode = CrawlMode::Y8;
    }
    else if("youtube" == modeString || "CrawlerMode::Youtube" == modeString || "CrawlMode::Youtube" == modeString)
    {
        mode = CrawlMode::Youtube;
    }
    return mode;
}

CrawlState WebCrawler::convertStringToCrawlerState(string const& stateString) const
{
    CrawlState state(CrawlState::Empty);
    if("CrawlState::Empty" == stateString)    {
        state = CrawlState::Empty;
    }
    else if("CrawlState::Active" == stateString)
    {
        state = CrawlState::Active;
    }
    else if("CrawlState::DownloadedFileIsInvalid" == stateString)
    {
        state = CrawlState::DownloadedFileIsInvalid;
    }
    else if("CrawlState::LinksAreInvalid" == stateString)
    {
        state = CrawlState::LinksAreInvalid;
    }
    else if("CrawlState::NextLinkIsInvalid" == stateString)
    {
        state = CrawlState::NextLinkIsInvalid;
    }
    return state;
}

bool WebCrawler::isCrawlStateInvalid() const
{
    return m_state == CrawlState::DownloadedFileIsInvalid ||
            m_state == CrawlState::LinksAreInvalid ||
            m_state == CrawlState::NextLinkIsInvalid;
}

bool WebCrawler::isWebLinksEmpty() const
{
    return m_webLinks.empty();
}

bool WebCrawler::isWebLinksValid() const
{
    return all_of(m_webLinks.begin(), m_webLinks.end(), [](string const& webLink)
    {        AlbaWebPathHandler webPathHandler(webLink);
        return !webPathHandler.isEmpty() && webPathHandler.hasProtocol();
    });
}

string WebCrawler::getUserInputAfterManuallyUsingMozillaFirefox(AlbaWebPathHandler const& webPathHandler) const
{
    constexpr int bufferSize = 1000;
    char buffer[bufferSize];    gotoLinkManuallyUsingMozillaFirefox(webPathHandler);
    cout<<"Enter user input:"<<endl;
    cin.getline(buffer, bufferSize);
    return string(buffer);
}

void WebCrawler::gotoLinkManuallyUsingMozillaFirefox(AlbaWebPathHandler const& webPathHandler) const
{
    string firefoxCommand(string(FIREFOX_EXECUTABLE_PATH)+R"( ")"+webPathHandler.getFullPath()+R"(")");
    cout << firefoxCommand << endl;    system(firefoxCommand.c_str());
}

}
