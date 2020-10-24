#include <File/AlbaFileReader.hpp>
#include <String/AlbaStringHelper.hpp>
#include <Crawlers/OneDownloadPerPageCrawler.hpp>
#include <CrawlHelpers/Downloaders.hpp>
#include <iostream>

using namespace alba;
using namespace alba::stringHelper;
using namespace aprgWebCrawler::Downloaders;
using namespace std;

namespace aprgWebCrawler
{

OneDownloadPerPageCrawler::OneDownloadPerPageCrawler(WebCrawler & webCrawler)
    : m_webCrawler(webCrawler)
    , m_configuration(webCrawler.getCrawlMode())
    , m_mode(webCrawler.getCrawlMode())
{}

void OneDownloadPerPageCrawler::crawl()
{
    cout << "OneDownloadPerPageCrawler::crawl" << endl;
    for(int webLinkIndex=0; webLinkIndex<m_webCrawler.getNumberOfWebLinks(); webLinkIndex++)
    {
        crawl(webLinkIndex);
    }
}

void OneDownloadPerPageCrawler::crawl(int webLinkIndex)
{
    while(!m_webCrawler.isOnInvalidCrawlState())
    {
        m_webCrawler.saveStateToMemoryCard(CrawlState::Active);
        AlbaWebPathHandler webLinkPathHandler(m_webCrawler.getWebLinkAtIndex(webLinkIndex));
        retrieveLinks(webLinkPathHandler);
        if(checkLinks())
        {
            downloadFile(webLinkPathHandler);
        }
        if(m_webCrawler.isOnCrawlStatesWhichRetryIsNeeded())
        {
            continue;
        }
        if(m_webCrawler.isOnCurrentDownloadFinishedCrawlState())
        {
            gotoNextLink(webLinkPathHandler, webLinkIndex);
        }
    }
}

void OneDownloadPerPageCrawler::retrieveLinks(AlbaWebPathHandler const& webLinkPathHandler)
{
    clearLinks();
    switch(m_mode)
    {
    case CrawlMode::Gehen:
        retrieveLinksForGehen(webLinkPathHandler);
        break;
    case CrawlMode::GuroManga:
        retrieveLinksForGuroManga(webLinkPathHandler);
        break;
    case CrawlMode::HBrowse:
        retrieveLinksForHBrowse(webLinkPathHandler);
        break;
    case CrawlMode::Hentai2Read:
        retrieveLinksForHentai2Read(webLinkPathHandler);
        break;
    case CrawlMode::Mangafox:
        retrieveLinksForMangaFox(webLinkPathHandler);
        break;
    case CrawlMode::MangafoxWithVolume:
        retrieveLinksForMangaFoxSaveInVolumeAndChapter(webLinkPathHandler);
        break;
    case CrawlMode::Mangahere:
        retrieveLinksForMangaHere(webLinkPathHandler);
        break;
    case CrawlMode::MangaPark:
        retrieveLinksForMangaPark(webLinkPathHandler);
        break;
    case CrawlMode::ChiaAnime:
    case CrawlMode::DoujinMoe:
    case CrawlMode::Youtube:
    case CrawlMode::Y8:
        cout << "OneDownloadPerPageCrawler::retrieveLinks | Mode is different" << endl;
        break;
    case CrawlMode::Empty:
    case CrawlMode::Unknown:
        cout << "OneDownloadPerPageCrawler::retrieveLinks | Mode is not set" << endl;
        break;
    }
}

bool OneDownloadPerPageCrawler::checkLinks()
{
    bool result(true);
    if(areLinksInvalid())
    {
        cout << "Links are invalid." << endl;
        printLinks();
        m_webCrawler.saveStateToMemoryCard(CrawlState::LinksAreInvalid);
        result = false;
    }
    return result;
}

void OneDownloadPerPageCrawler::downloadFile(AlbaWebPathHandler const& webLinkPathHandler)
{
    AlbaWebPathHandler fileToDownloadWebPathHandler(webLinkPathHandler);
    fileToDownloadWebPathHandler.gotoLink(m_linkForCurrentFileToDownload);
    if(!fileToDownloadWebPathHandler.isFile())
    {
        cout << "Link is not to a file." << endl;
        cout << "Link of file to Download: " << fileToDownloadWebPathHandler.getFullPath() << endl;
        m_webCrawler.saveStateToMemoryCard(CrawlState::LinksAreInvalid);
    }
    else
    {
        AlbaWindowsPathHandler downloadPathHandler(m_localPathForCurrentFileToDownload);
        downloadPathHandler.createDirectoriesForNonExisitingDirectories();
        downloadBinaryFile(fileToDownloadWebPathHandler, downloadPathHandler, m_webCrawler.getCrawlMode());
        if(downloadPathHandler.getFileSizeEstimate() < m_configuration.getMinimumFileSize())
        {
            cout << "Download file size is less than " << m_configuration.getMinimumFileSize() << ". FileSize = " << downloadPathHandler.getFileSizeEstimate() << " Invalid file. Retrying from the start" << endl;
            m_webCrawler.saveStateToMemoryCard(CrawlState::DownloadedFileSizeIsLessThanExpected);
        }
        else
        {
            m_webCrawler.saveStateToMemoryCard(CrawlState::CurrentDownloadIsFinished);
        }
    }
}

void OneDownloadPerPageCrawler::gotoNextLink(AlbaWebPathHandler const& webLinkPathHandler, int webLinkIndex)
{
    if(m_linkForNextHtml.empty())
    {
        cout << "Terminating the because next web link is empty." << endl;
        m_webCrawler.saveStateToMemoryCard(CrawlState::NextLinkIsInvalid);
    }
    else
    {
        AlbaWebPathHandler nextWebPathHandler(webLinkPathHandler);
        nextWebPathHandler.gotoLink(m_linkForNextHtml);
        if(webLinkPathHandler.getFullPath() == nextWebPathHandler.getFullPath())
        {
            cout << "Crawler stop because the next web link is the same as previous link." << endl;
            m_webCrawler.saveStateToMemoryCard(CrawlState::NextLinkIsInvalid);
        }
        else
        {
            m_webCrawler.modifyWebLink(nextWebPathHandler.getFullPath(), webLinkIndex);
        }
    }
}

void OneDownloadPerPageCrawler::clearLinks()
{
    m_linkForNextHtml.clear();
    m_linkForCurrentFileToDownload.clear();
    m_localPathForCurrentFileToDownload.clear();
}

bool OneDownloadPerPageCrawler::areLinksInvalid() const
{
    return m_linkForCurrentFileToDownload.empty() || m_localPathForCurrentFileToDownload.empty();
}

void OneDownloadPerPageCrawler::printLinks() const
{
    cout << "LinkForNextHtml : " << m_linkForNextHtml << endl;
    cout << "LinkForCurrentFileToDownload : " << m_linkForCurrentFileToDownload << endl;
    cout << "LocalPathForCurrentFileToDownload : " << m_localPathForCurrentFileToDownload << endl;
}

}
