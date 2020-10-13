#include "AprgWebCrawler.hpp"

#include <CrawlConfiguration/CrawlConfiguration.hpp>
#include <iostream>

using namespace std;

namespace alba
{

void AprgWebCrawler::crawlOneHtmlAndOneFileToDownload()
{
    for(string & webLink : m_webLinks)
    {
        crawlOneHtmlAndOneFileToDownload(webLink);
    }
}

void AprgWebCrawler::crawlOneHtmlAndOneFileToDownload(string& webLink)
{
    cout << "AprgWebCrawler::crawlPerHtmlAndDownloadImage" << endl;

    CrawlConfiguration configuration(m_mode);
    while(!isCrawlStateInvalid())
    {
        AlbaWebPathHandler currentWebLinkPathHandler(webLink);
        AlbaWindowsPathHandler downloadPathHandler(m_workingPathHandler.getDirectory() + R"(\temp.html)");
        downloadFileAsText(currentWebLinkPathHandler, downloadPathHandler);
        LinksForHtmlAndFileToDownload links(getLinks(currentWebLinkPathHandler, downloadPathHandler.getFullPath()));
        if(links.isInvalid())
        {
            cout << "Links are invalid." << endl;
            links.printLinks();
            saveInvalidStateToMemoryCard(CrawlState::LinksAreInvalid);
            break;
        }
        AlbaWebPathHandler fileToDownloadWebPathHandler(currentWebLinkPathHandler);
        fileToDownloadWebPathHandler.gotoLink(links.linkForCurrentFileToDownload);
        if(!fileToDownloadWebPathHandler.isFile())
        {
            cout << "Link is not to a file." << endl;
            cout << "Link of file to Download: " << fileToDownloadWebPathHandler.getFullPath() << endl;
            saveInvalidStateToMemoryCard(CrawlState::LinksAreInvalid);
            break;
        }
        downloadPathHandler.input(links.localPathForCurrentFileToDownload);
        downloadPathHandler.createDirectoriesIfItDoesNotExist();
        downloadBinaryFile(fileToDownloadWebPathHandler, downloadPathHandler);
        if(downloadPathHandler.getFileSizeEstimate() < configuration.getMinimumFileSize())
        {
            cout << "Download file size is less than "<<configuration.getMinimumFileSize()<<". FileSize = "<< downloadPathHandler.getFileSizeEstimate() <<" Invalid file. Retrying from the start" << endl;
            continue;
        }
        if(links.linkForNextHtml.empty())
        {
            cout << "Terminating the because next web link is empty." << endl;
            saveInvalidStateToMemoryCard(CrawlState::NextLinkIsInvalid);
            break;
        }
        AlbaWebPathHandler nextWebPathHandler(currentWebLinkPathHandler);
        nextWebPathHandler.gotoLink(links.linkForNextHtml);
        if(currentWebLinkPathHandler.getFullPath() == nextWebPathHandler.getFullPath())
        {
            cout << "Crawler stop because the next web link is the same as previous link." << endl;
            saveInvalidStateToMemoryCard(CrawlState::NextLinkIsInvalid);
            break;
        }
        webLink = nextWebPathHandler.getFullPath();
        saveMemoryCard();
    }
}

LinksForHtmlAndFileToDownload AprgWebCrawler::getLinks(AlbaWebPathHandler const& webLinkPathHandler, string const& pathOfHtmlFile) const
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
        cout << "AprgWebCrawler::getLinks | Mode is not recognized" << endl;
        break;
    case CrawlMode::Empty:
        cout << "AprgWebCrawler::getLinks | Mode is not set" << endl;
        break;
    }
    return LinksForHtmlAndFileToDownload();
}

}
