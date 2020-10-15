#include "WebCrawler.hpp"

#include <AlbaFileReader.hpp>
#include <AlbaStringHelper.hpp>
#include <algorithm>
#include <fstream>
#include <iostream>

#define FIREFOX_EXECUTABLE_PATH R"(C:\"Program Files"\"Mozilla Firefox"\firefox.exe)"
#define APRG_WEB_CRAWLER_TEMP_HTML_FILE R"(C:\APRG\AprgWebCrawler\temp.html)"

using namespace alba;
using namespace alba::stringHelper;
using namespace std;

namespace aprgWebCrawler
{

WebCrawler::WebCrawler(string const& downloadDirectory)
    : m_mode(CrawlMode::Unknown)
    , m_state(CrawlState::Unknown)
    , m_downloadDirectoryPathHandler(downloadDirectory + R"(\)")
    , m_memoryCardPathHandler(downloadDirectory + R"(\MemoryCard.txt)")
{
    if (m_memoryCardPathHandler.isFoundInLocalSystem() && m_memoryCardPathHandler.isFile())
    {
        loadMemoryCard();
    }
}

WebCrawler::WebCrawler(string const& workingDirectory, string const& webLink)
    : m_mode(convertWebLinkToCrawlerMode(webLink))
    , m_state(CrawlState::Unknown)
    , m_downloadDirectoryPathHandler(workingDirectory + R"(\)" + getTitle(webLink) + R"(\)")
    , m_memoryCardPathHandler(m_downloadDirectoryPathHandler.getFullPath() + R"(\MemoryCard.txt)")
{
    m_webLinks.push_back(webLink);
    m_memoryCardPathHandler.createDirectoriesIfItDoesNotExist();
    saveMemoryCard();
    m_downloadDirectoryPathHandler.reInput();
    m_memoryCardPathHandler.reInput();
}

bool WebCrawler::isValid() const
{
    return m_downloadDirectoryPathHandler.isFoundInLocalSystem() &&
            m_downloadDirectoryPathHandler.isDirectory() &&
            m_memoryCardPathHandler.isFoundInLocalSystem() &&
            m_memoryCardPathHandler.isFile() &&
            isModeRecognized() &&
            !isWebLinksEmpty() &&
            isWebLinksValid();
}

void WebCrawler::printStatus() const
{
    if(!m_downloadDirectoryPathHandler.isFoundInLocalSystem())
    {
        cout << "Working directory: ["<< m_downloadDirectoryPathHandler.getFullPath() << "] is not found" << endl;
    }
    else if(!m_downloadDirectoryPathHandler.isDirectory())
    {
        cout << "Working directory: ["<< m_downloadDirectoryPathHandler.getFullPath() << "] is not a directory" << endl;
    }
    else if(!m_memoryCardPathHandler.isFoundInLocalSystem())
    {
        cout << "Memory card: ["<< m_downloadDirectoryPathHandler.getFullPath() << "] is not found" << endl;
    }
    else if(!m_memoryCardPathHandler.isFile())
    {
        cout << "Memory card: ["<< m_downloadDirectoryPathHandler.getFullPath() << "] is not a file" << endl;
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
    else if(isModeRecognized())
    {
        cout << "Mode: ["<< getCrawlModeString() << "] is not a recognized mode" << endl;
    }
    else
    {
        cout << "Status is okay" << endl;
    }
}

CrawlMode WebCrawler::getCrawlMode() const
{
    return m_mode;
}

CrawlState WebCrawler::getCrawlState() const
{
    return m_state;
}

string WebCrawler::getCrawlModeString() const
{
    return convertCrawlerModeToString(m_mode);
}

string WebCrawler::getCrawlStateString() const
{
    return convertCrawlerStateToString(m_state);
}

string WebCrawler::getTitleFromFirstWebLink() const
{
    return getTitle(getFirstWebLink());
}

string WebCrawler::getTitle(string const& webLink) const
{
    string title;
    switch(convertWebLinkToCrawlerMode(webLink))
    {
    case CrawlMode::ChiaAnime:
        title = getTitleFromTitleWindow(webLink);
        title = getStringInBetweenTwoStrings(title, "Watch", "Episode");
        break;
    case CrawlMode::Gehen:
    case CrawlMode::GuroManga:
    case CrawlMode::HBrowse:
    case CrawlMode::Y8:
    case CrawlMode::Youtube:
        title = getTitleFromTitleWindow(webLink);
        break;
    case CrawlMode::Hentai2Read:
        title = getTitleFromTitleWindow(webLink);
        title = getStringBeforeThisString(title, "Hentai - Read");
        break;
    case CrawlMode::Mangafox:
    case CrawlMode::MangafoxWithVolume:
    case CrawlMode::Mangahere:
    case CrawlMode::MangaPark:
        title = getStringInBetweenTwoStrings(AlbaWebPathHandler(getFirstWebLink()).getFullPath(), R"(/manga/)", R"(/)");
        break;
    case CrawlMode::Empty:
    case CrawlMode::Unknown:
        cout << "WebCrawler::getTitle | Mode is not set" << endl;
        break;
    }
    if(title.empty())
    {
        title = "TempTitle";
    }
    title = getStringAndReplaceNonAlphanumericCharactersToUnderScore(title);
    title = getStringWithoutStartingAndTrailingCharacters(title, "_");
    cout << "WebCrawler::getTitle | title: " << title << endl;
    return title;
}

std::string WebCrawler::getFirstWebLink() const
{
    string webLink;
    if(m_webLinks.size() > 0)
    {
        webLink = *(m_webLinks.begin());
    }
    return webLink;
}

std::string WebCrawler::getDownloadDirectory() const
{
    return m_downloadDirectoryPathHandler.getDirectory();
}

string WebCrawler::getTitleFromTitleWindow(string const& webLink) const
{
    string title;
    AlbaWebPathHandler webLinkPathHandler(webLink);
    AlbaWindowsPathHandler downloadPathHandler(APRG_WEB_CRAWLER_TEMP_HTML_FILE);
    downloadFileAsText(webLinkPathHandler, downloadPathHandler);
    ifstream htmlFileStream(downloadPathHandler.getFullPath());
    if(!htmlFileStream.is_open())
    {
        cout << "Cannot open html file." << endl;
        cout << "File to read:" << downloadPathHandler.getFullPath() << endl;
    }
    else
    {
        AlbaFileReader htmlFileReader(htmlFileStream);
        while (htmlFileReader.isNotFinished())
        {
            string lineInHtmlFile(htmlFileReader.simpleGetLine());
            if(isStringFoundInsideTheOtherStringCaseSensitive(lineInHtmlFile, R"(<title>)"))
            {
                title = getStringInBetweenTwoStrings(lineInHtmlFile, R"(<title>)", R"(</title>)");
            }
        }
    }
    return title;
}

void WebCrawler::saveMemoryCard() const
{
    ofstream memoryCardStream(m_memoryCardPathHandler.getFullPath());
    if(memoryCardStream.is_open())
    {
        memoryCardStream << getCrawlModeString() << endl;
        memoryCardStream << getCrawlStateString() << endl;
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
    if(memoryCardStream.is_open())
    {
        AlbaFileReader memoryCardReader(memoryCardStream);
        while(memoryCardReader.isNotFinished())
        {
            string lineFromMemoryCard(memoryCardReader.getLineAndIgnoreWhiteSpaces());
            CrawlMode possibleMode(convertStringToCrawlerMode(lineFromMemoryCard));
            CrawlState possibleState(convertStringToCrawlerState(lineFromMemoryCard));
            AlbaWebPathHandler webPathHandler(lineFromMemoryCard);
            if(CrawlMode::Empty != possibleMode)
            {
                setCrawlMode(possibleMode);
            }
            else if(CrawlState::Empty != possibleState)
            {
                setCrawlState(possibleState);
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
    case CrawlMode::Empty:
    case CrawlMode::Unknown:
        cout<<"WebCrawler::crawl | CrawlMode is still not set."<<endl;
        break;
    }
}

void WebCrawler::setCrawlMode(CrawlMode mode)
{
    m_mode = mode;
}

void WebCrawler::setCrawlState(CrawlState state)
{
    m_state = state;
}

void WebCrawler::saveStateToMemoryCard(CrawlState state)
{
    setCrawlState(state);
    saveMemoryCard();
}

CrawlMode WebCrawler::convertStringToCrawlerMode(string const& modeString) const
{
    CrawlMode mode(CrawlMode::Empty);
    if("CrawlMode::Unknown" == modeString)
    {
        mode = CrawlMode::Unknown;
    }
    else if("chiaanime" == modeString || "CrawlerMode::ChiaAnime" == modeString || "CrawlMode::ChiaAnime" == modeString)
    {
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

CrawlMode WebCrawler::convertWebLinkToCrawlerMode(string const& webLink) const
{
    CrawlMode mode(CrawlMode::Empty);
    if(stringHelper::isStringFoundInsideTheOtherStringNotCaseSensitive(webLink, "chia-anime.tv"))
    {
        mode = CrawlMode::ChiaAnime;
    }
    else if(stringHelper::isStringFoundInsideTheOtherStringNotCaseSensitive(webLink, "g.e-hentai.org"))
    {
        mode = CrawlMode::Gehen;
    }
    else if(stringHelper::isStringFoundInsideTheOtherStringNotCaseSensitive(webLink, "guromanga.com"))
    {
        mode = CrawlMode::GuroManga;
    }
    else if(stringHelper::isStringFoundInsideTheOtherStringNotCaseSensitive(webLink, "hbrowse.com"))
    {
        mode = CrawlMode::HBrowse;
    }
    else if(stringHelper::isStringFoundInsideTheOtherStringNotCaseSensitive(webLink, "hentai2read.com"))
    {
        mode = CrawlMode::Hentai2Read;
    }
    else if(stringHelper::isStringFoundInsideTheOtherStringNotCaseSensitive(webLink, "mangafox.me"))
    {
        mode = CrawlMode::Mangafox;
    }
    else if(stringHelper::isStringFoundInsideTheOtherStringNotCaseSensitive(webLink, "mangafox.me"))
    {
        mode = CrawlMode::MangafoxWithVolume;
    }
    else if(stringHelper::isStringFoundInsideTheOtherStringNotCaseSensitive(webLink, "mangahere.co"))
    {
        mode = CrawlMode::Mangahere;
    }
    else if(stringHelper::isStringFoundInsideTheOtherStringNotCaseSensitive(webLink, "mangapark.me"))
    {
        mode = CrawlMode::MangaPark;
    }
    else if(stringHelper::isStringFoundInsideTheOtherStringNotCaseSensitive(webLink, "y8.com"))
    {
        mode = CrawlMode::Y8;
    }
    else if(stringHelper::isStringFoundInsideTheOtherStringNotCaseSensitive(webLink, "youtube.com"))
    {
        mode = CrawlMode::Youtube;
    }
    return mode;
}

CrawlState WebCrawler::convertStringToCrawlerState(string const& stateString) const
{
    CrawlState state(CrawlState::Empty);
    if("CrawlState::Unknown" == stateString)
    {
        state = CrawlState::Unknown;
    }
    else if("CrawlState::Active" == stateString)
    {
        state = CrawlState::Active;
    }
    else if("CrawlState::DownloadedFileIsInvalid" == stateString)
    {
        state = CrawlState::DownloadedFileIsInvalid;
    }
    else if("CrawlState::DownloadedFileSizeIsLessThanExpected" == stateString)
    {
        state = CrawlState::DownloadedFileSizeIsLessThanExpected;
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

#define GET_ENUM_STRING(en) \
    case en: \
    return #en;

string WebCrawler::convertCrawlerModeToString(CrawlMode mode) const
{
    switch(mode)
    {
    GET_ENUM_STRING(CrawlMode::Empty)
    GET_ENUM_STRING(CrawlMode::Unknown)
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

string WebCrawler::convertCrawlerStateToString(CrawlState state) const
{
    switch(state)
    {
    GET_ENUM_STRING(CrawlState::Empty)
    GET_ENUM_STRING(CrawlState::Unknown)
            GET_ENUM_STRING(CrawlState::Active)
            GET_ENUM_STRING(CrawlState::DownloadedFileIsInvalid)
            GET_ENUM_STRING(CrawlState::DownloadedFileSizeIsLessThanExpected)
            GET_ENUM_STRING(CrawlState::LinksAreInvalid)
            GET_ENUM_STRING(CrawlState::NextLinkIsInvalid)
    }
    return "";
}

#undef GET_ENUM_STRING

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
    {
        AlbaWebPathHandler webPathHandler(webLink);
        return !webPathHandler.isEmpty() && webPathHandler.hasProtocol();
    });
}

bool WebCrawler::isModeRecognized() const
{
    return CrawlMode::Unknown == m_mode;
}

string WebCrawler::getUserInputAfterManuallyUsingMozillaFirefox(AlbaWebPathHandler const& webPathHandler) const
{
    constexpr int bufferSize = 1000;
    char buffer[bufferSize];
    gotoLinkManuallyUsingMozillaFirefox(webPathHandler);
    cout<<"Enter user input:"<<endl;
    cin.getline(buffer, bufferSize);
    return string(buffer);
}

void WebCrawler::gotoLinkManuallyUsingMozillaFirefox(AlbaWebPathHandler const& webPathHandler) const
{
    string firefoxCommand(string(FIREFOX_EXECUTABLE_PATH)+R"( ")"+webPathHandler.getFullPath()+R"(")");
    cout << firefoxCommand << endl;
    system(firefoxCommand.c_str());
}

}
