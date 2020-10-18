#include "WebCrawler.hpp"

#include <AlbaFileReader.hpp>
#include <AlbaStringHelper.hpp>
#include <CrawlConfiguration/CrawlConfiguration.hpp>
#include <iostream>

using namespace alba;
using namespace alba::stringHelper;
using namespace std;

namespace aprgWebCrawler
{

void WebCrawler::crawlOneHtmlAndOneFileToDownload()
{
    for(string & webLink : m_webLinks)
    {
        crawlOneHtmlAndOneFileToDownload(webLink);
    }
}

void WebCrawler::crawlOneHtmlAndOneFileToDownload(string& webLink)
{
    cout << "WebCrawler::crawlPerHtmlAndDownloadImage" << endl;

    CrawlConfiguration configuration(m_mode);
    while(!isCrawlStateInvalid())
    {
        AlbaWebPathHandler currentWebLinkPathHandler(webLink);
        AlbaWindowsPathHandler downloadPathHandler(m_downloadDirectoryPathHandler.getDirectory() + R"(\temp.html)");
        downloadFileAsText(currentWebLinkPathHandler, downloadPathHandler);
        LinksForHtmlAndFileToDownload links(getLinks(currentWebLinkPathHandler, downloadPathHandler.getFullPath()));
        if(links.isInvalid())
        {
            cout << "Links are invalid." << endl;
            links.printLinks();
            saveStateToMemoryCard(CrawlState::LinksAreInvalid);
            break;
        }
        AlbaWebPathHandler fileToDownloadWebPathHandler(currentWebLinkPathHandler);
        fileToDownloadWebPathHandler.gotoLink(links.linkForCurrentFileToDownload);
        if(!fileToDownloadWebPathHandler.isFile())
        {
            cout << "Link is not to a file." << endl;
            cout << "Link of file to Download: " << fileToDownloadWebPathHandler.getFullPath() << endl;
            saveStateToMemoryCard(CrawlState::LinksAreInvalid);
            break;
        }
        downloadPathHandler.input(links.localPathForCurrentFileToDownload);
        downloadPathHandler.createDirectoriesForNonExisitingDirectories();
        downloadBinaryFile(fileToDownloadWebPathHandler, downloadPathHandler);
        if(downloadPathHandler.getFileSizeEstimate() < configuration.getMinimumFileSize())
        {
            cout << "Download file size is less than "<<configuration.getMinimumFileSize()<<". FileSize = "<< downloadPathHandler.getFileSizeEstimate() <<" Invalid file. Retrying from the start" << endl;
            saveStateToMemoryCard(CrawlState::DownloadedFileSizeIsLessThanExpected);
            continue;
        }
        if(links.linkForNextHtml.empty())
        {
            cout << "Terminating the because next web link is empty." << endl;
            saveStateToMemoryCard(CrawlState::NextLinkIsInvalid);
            break;
        }
        AlbaWebPathHandler nextWebPathHandler(currentWebLinkPathHandler);
        nextWebPathHandler.gotoLink(links.linkForNextHtml);
        if(currentWebLinkPathHandler.getFullPath() == nextWebPathHandler.getFullPath())
        {
            cout << "Crawler stop because the next web link is the same as previous link." << endl;
            saveStateToMemoryCard(CrawlState::NextLinkIsInvalid);
            break;
        }
        webLink = nextWebPathHandler.getFullPath();
        setCrawlState(CrawlState::Active);
        saveMemoryCard();
    }
}

LinksForHtmlAndFileToDownload WebCrawler::getLinks(AlbaWebPathHandler const& webLinkPathHandler, string const& pathOfHtmlFile) const
{
    switch(m_mode)
    {
    case CrawlMode::Gehen:
        return getLinksForGehen(webLinkPathHandler, pathOfHtmlFile);
    case CrawlMode::GuroManga:
        return getLinksForGuroManga(webLinkPathHandler, pathOfHtmlFile);
    case CrawlMode::HBrowse:
        return getLinksForHBrowse(webLinkPathHandler, pathOfHtmlFile);
    case CrawlMode::Hentai2Read:
        return getLinksForHentai2Read(webLinkPathHandler, pathOfHtmlFile);
    case CrawlMode::Mangafox:
        return getLinksForMangaFox(webLinkPathHandler, pathOfHtmlFile);
    case CrawlMode::MangafoxWithVolume:
        return getLinksForMangaFoxSaveInVolumeAndChapter(webLinkPathHandler, pathOfHtmlFile);
    case CrawlMode::Mangahere:
        return getLinksForMangaHere(webLinkPathHandler, pathOfHtmlFile);
    case CrawlMode::MangaPark:
        return getLinksForMangaPark(webLinkPathHandler, pathOfHtmlFile);
    case CrawlMode::Y8:
        return getLinksForY8(webLinkPathHandler, pathOfHtmlFile);
    case CrawlMode::ChiaAnime:
    case CrawlMode::Youtube:
        cout << "WebCrawler::getLinks | Mode is not recognized" << endl;
        break;
    case CrawlMode::Empty:
    case CrawlMode::Unknown:
        cout << "WebCrawler::getLinks | Mode is not set" << endl;
        break;
    }
    return LinksForHtmlAndFileToDownload();
}

}
