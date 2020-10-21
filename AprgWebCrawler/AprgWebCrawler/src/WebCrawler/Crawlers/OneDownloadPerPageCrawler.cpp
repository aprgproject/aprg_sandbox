#include <AlbaFileReader.hpp>
#include <AlbaStringHelper.hpp>
#include <Crawlers/OneDownloadPerPageCrawler.hpp>
#include <iostream>

using namespace alba;
using namespace alba::stringHelper;
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
    while(!m_webCrawler.isCrawlStateInvalid())
    {
        AlbaWebPathHandler webLinkPathHandler(m_webCrawler.getWebLinkAtIndex(webLinkIndex));
        retrieveLinks(webLinkPathHandler);
        if(areLinksInvalid())
        {
            cout << "Links are invalid." << endl;            printLinks();
            m_webCrawler.saveStateToMemoryCard(CrawlState::LinksAreInvalid);
            break;
        }
        AlbaWebPathHandler fileToDownloadWebPathHandler(webLinkPathHandler);
        fileToDownloadWebPathHandler.gotoLink(m_linkForCurrentFileToDownload);
        if(!fileToDownloadWebPathHandler.isFile())
        {            cout << "Link is not to a file." << endl;
            cout << "Link of file to Download: " << fileToDownloadWebPathHandler.getFullPath() << endl;
            m_webCrawler.saveStateToMemoryCard(CrawlState::LinksAreInvalid);
            break;        }
        AlbaWindowsPathHandler downloadPathHandler(m_localPathForCurrentFileToDownload);
        downloadPathHandler.createDirectoriesForNonExisitingDirectories();
        m_webCrawler.downloadBinaryFile(fileToDownloadWebPathHandler, downloadPathHandler);
        if(downloadPathHandler.getFileSizeEstimate() < m_configuration.getMinimumFileSize())
        {
            cout << "Download file size is less than " << m_configuration.getMinimumFileSize() << ". FileSize = " << downloadPathHandler.getFileSizeEstimate() << " Invalid file. Retrying from the start" << endl;
            m_webCrawler.saveStateToMemoryCard(CrawlState::DownloadedFileSizeIsLessThanExpected);
            continue;
        }
        if(m_linkForNextHtml.empty())
        {
            cout << "Terminating the because next web link is empty." << endl;
            m_webCrawler.saveStateToMemoryCard(CrawlState::NextLinkIsInvalid);
            break;
        }
        AlbaWebPathHandler nextWebPathHandler(webLinkPathHandler);
        nextWebPathHandler.gotoLink(m_linkForNextHtml);
        if(webLinkPathHandler.getFullPath() == nextWebPathHandler.getFullPath())
        {
            cout << "Crawler stop because the next web link is the same as previous link." << endl;
            m_webCrawler.saveStateToMemoryCard(CrawlState::NextLinkIsInvalid);
            break;
        }
        m_webCrawler.modifyWebLink(nextWebPathHandler.getFullPath(), webLinkIndex);
        m_webCrawler.saveStateToMemoryCard(CrawlState::Active);
    }
}
void OneDownloadPerPageCrawler::retrieveLinks(AlbaWebPathHandler const& webLinkPathHandler)
{
    clearLinks();    switch(m_mode)
    {
    case CrawlMode::Gehen:
        retrieveLinksForGehen(webLinkPathHandler);
    case CrawlMode::GuroManga:
        retrieveLinksForGuroManga(webLinkPathHandler);
    case CrawlMode::HBrowse:
        retrieveLinksForHBrowse(webLinkPathHandler);
    case CrawlMode::Hentai2Read:
        retrieveLinksForHentai2Read(webLinkPathHandler);
    case CrawlMode::Mangafox:
        retrieveLinksForMangaFox(webLinkPathHandler);
    case CrawlMode::MangafoxWithVolume:
        retrieveLinksForMangaFoxSaveInVolumeAndChapter(webLinkPathHandler);
    case CrawlMode::Mangahere:
        retrieveLinksForMangaHere(webLinkPathHandler);
    case CrawlMode::MangaPark:
        retrieveLinksForMangaPark(webLinkPathHandler);
    case CrawlMode::Y8:
    case CrawlMode::ChiaAnime:
    case CrawlMode::Youtube:
        cout << "OneDownloadPerPageCrawler::retrieveLinks | Mode is not recognized" << endl;
        break;
    case CrawlMode::Empty:
    case CrawlMode::Unknown:
        cout << "OneDownloadPerPageCrawler::retrieveLinks | Mode is not set" << endl;
        break;
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
