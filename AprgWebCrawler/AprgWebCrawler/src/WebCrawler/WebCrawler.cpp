#include "WebCrawler.hpp"

#include <File/AlbaFileReader.hpp>
#include <String/AlbaStringHelper.hpp>
#include <algorithm>
#include <Crawlers/ChiaAnimeCrawler.hpp>
#include <Crawlers/DoujinMoeCrawler.hpp>
#include <Crawlers/OneDownloadPerPageCrawler.hpp>
#include <Crawlers/Y8Crawler.hpp>
#include <Crawlers/Youtube.hpp>
#include <CrawlHelpers/Downloaders.hpp>
#include <fstream>
#include <iostream>

using namespace alba;
using namespace alba::stringHelper;
using namespace aprgWebCrawler::Downloaders;
using namespace std;

namespace aprgWebCrawler
{

WebCrawler::WebCrawler(string const& downloadDirectory, string const& temporaryFilePath)
    : m_mode(CrawlMode::Unknown)
    , m_state(CrawlState::Unknown)
    , m_temporaryFilePath(temporaryFilePath)
    , m_downloadDirectoryPathHandler(downloadDirectory + R"(\)")
    , m_memoryCardPathHandler(downloadDirectory + R"(\MemoryCard.txt)")
{
    if (m_memoryCardPathHandler.isFoundInLocalSystem() && m_memoryCardPathHandler.isFile())
    {
        loadMemoryCard();
    }
}

WebCrawler::WebCrawler(string const& workingDirectory, string const& webLink, string const& temporaryFilePath)
    : m_mode(convertWebLinkToCrawlerMode(webLink))
    , m_state(CrawlState::Unknown)
    , m_temporaryFilePath(temporaryFilePath)
    , m_downloadDirectoryPathHandler(workingDirectory + R"(\)" + getNewDirectoryNameFromWeblink(webLink) + R"(\)")
    , m_memoryCardPathHandler(m_downloadDirectoryPathHandler.getFullPath() + R"(\MemoryCard.txt)")
{
    m_webLinks.push_back(webLink);
    m_memoryCardPathHandler.createDirectoriesForNonExisitingDirectories();
    saveMemoryCard();
    m_downloadDirectoryPathHandler.reInput();
    m_memoryCardPathHandler.reInput();
}

void WebCrawler::crawl()
{
    switch(m_mode)
    {
    case CrawlMode::ChiaAnime:
    {
        ChiaAnimeCrawler chiaAnimeCrawler(*this);
        chiaAnimeCrawler.crawl();
        break;
    }
    case CrawlMode::DoujinMoe:
    {
        DoujinMoeCrawler doujinMoeCrawler(*this);
        doujinMoeCrawler.crawl();
        break;
    }
    case CrawlMode::Gehen:
    case CrawlMode::GuroManga:
    case CrawlMode::HBrowse:
    case CrawlMode::Hentai2Read:
    case CrawlMode::Mangafox:
    case CrawlMode::MangafoxWithVolume:
    case CrawlMode::Mangahere:
    case CrawlMode::MangaPark:
    {
        OneDownloadPerPageCrawler oneDownloadPerPageCrawler(*this);
        oneDownloadPerPageCrawler.crawl();
        break;
    }
    case CrawlMode::Y8:
    {
        Y8Crawler y8Crawler(*this);
        y8Crawler.crawl();
        break;
    }
    case CrawlMode::Youtube:
    {
        Youtube youtubeCrawler(*this);
        youtubeCrawler.crawl();
        break;
    }
    case CrawlMode::Empty:
    case CrawlMode::Unknown:
        cout<<"WebCrawler::crawl | CrawlMode is still not set."<<endl;
        break;
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

string WebCrawler::getDownloadDirectory() const
{
    return m_downloadDirectoryPathHandler.getDirectory();
}

string WebCrawler::getNewDirectoryName() const
{
    return getNewDirectoryNameFromWeblink(getFirstWebLinkIfPossible());
}

string WebCrawler::getNewDirectoryNameFromWeblink(string const& webLink) const
{
    string title;
    switch(convertWebLinkToCrawlerMode(webLink))
    {
    case CrawlMode::ChiaAnime:
        title = getTitleFromTitleWindow(webLink);
        title = getStringInBetweenTwoStrings(title, "Watch", "Episode");
        break;
    case CrawlMode::DoujinMoe:
        title = getTitleFromTitleWindow(webLink);
        title = getStringAfterThisString(title, "Doujin-moe - ");
        break;
    case CrawlMode::Gehen:
    case CrawlMode::GuroManga:
    case CrawlMode::HBrowse:
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
        title = getStringInBetweenTwoStrings(webLink, R"(/manga/)", R"(/)");
        break;
    case CrawlMode::Y8:
        title = "Y8Games";
        break;
    case CrawlMode::Empty:
    case CrawlMode::Unknown:
        cout << "WebCrawler::getNewDirectoryNameFromWeblink | Mode is not set" << endl;
        break;
    }
    if(title.empty())
    {
        title = "TempTitle";
    }
    title = getStringAndReplaceNonAlphanumericCharactersToUnderScore(title);
    title = getStringWithoutStartingAndTrailingCharacters(title, "_");
    cout << "WebCrawler::getNewDirectoryNameFromWeblink | title: " << title << endl;
    return title;
}

int WebCrawler::getNumberOfWebLinks()
{
    return m_webLinks.size();
}

string WebCrawler::getWebLinkAtIndex(int index)
{
    return m_webLinks[index];
}

string WebCrawler::getFirstWebLinkIfPossible() const
{
    string webLink;
    if(!m_webLinks.empty())
    {
        webLink = *(m_webLinks.begin());
    }
    return webLink;
}

string WebCrawler::getTemporaryFilePath() const
{
    if(m_temporaryFilePath.empty())
    {
        cout<<"TemporaryFilePath is not set! Possible problem in download"<<endl;
    }
    return m_temporaryFilePath;
}

void WebCrawler::setTemporaryFilePath(string const& temporaryFilePath)
{
    m_temporaryFilePath = temporaryFilePath;
}

void WebCrawler::addWebLink(string const& webLink)
{
    m_webLinks.emplace_back(webLink);
}

void WebCrawler::modifyWebLink(string const& webLink, int index)
{
    m_webLinks[index]=webLink;
}

void WebCrawler::removeWebLink(int index)
{
    m_webLinks.erase(m_webLinks.begin()+index);
}

bool WebCrawler::isValid() const
{
    return m_downloadDirectoryPathHandler.isFoundInLocalSystem() &&
            m_downloadDirectoryPathHandler.isDirectory() &&
            m_memoryCardPathHandler.isFoundInLocalSystem() &&
            m_memoryCardPathHandler.isFile() &&
            isModeUnrecognized() &&
            !isWebLinksEmpty() &&
            isWebLinksValid();
}

bool WebCrawler::isOnInvalidCrawlState() const
{
    return m_state == CrawlState::DownloadedFileIsInvalid ||
            m_state == CrawlState::LinksAreInvalid ||
            m_state == CrawlState::NextLinkIsInvalid;
}

bool WebCrawler::isOnCrawlStatesWhichRetryIsNeeded() const
{
    return m_state == CrawlState::DownloadedFileSizeIsLessThanExpected ||
            m_state == CrawlState::DownloadFailsAndRetryIsNeeded;
}

bool WebCrawler::isOnCurrentDownloadFinishedCrawlState() const
{
    return m_state == CrawlState::CurrentDownloadIsFinished;
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

void WebCrawler::saveStateToMemoryCard(CrawlState state)
{
    setCrawlState(state);
    saveMemoryCard();
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
    else if(isModeUnrecognized())
    {
        cout << "Mode: ["<< getCrawlModeString() << "] is not a recognized mode" << endl;
    }
    else
    {
        cout << "Status is okay" << endl;
    }
}

string WebCrawler::getTitleFromTitleWindow(string const& webLink) const
{
    string title;
    AlbaWebPathHandler webLinkPathHandler(webLink);
    AlbaLocalPathHandler downloadPathHandler(getTemporaryFilePath());
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

bool WebCrawler::isModeUnrecognized() const
{
    return CrawlMode::Unknown == m_mode;
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

void WebCrawler::setCrawlMode(CrawlMode mode)
{
    m_mode = mode;
}

void WebCrawler::setCrawlState(CrawlState state)
{
    m_state = state;
}

}
