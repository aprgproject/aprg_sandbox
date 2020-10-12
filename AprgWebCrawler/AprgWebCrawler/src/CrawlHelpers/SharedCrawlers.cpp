#include "AprgWebCrawler.hpp"

#include <CurlInterface.hpp>
#include <iostream>

using namespace curl::CurlInterface;
using namespace std;

namespace alba
{

void AprgWebCrawler::crawlOneHtmlAndOneFileToDownload(int const minimumSizeOfDownload)
{
    for(string & webLink : m_webLinks)
    {
        crawlOneHtmlAndOneFileToDownload(webLink, minimumSizeOfDownload);
    }
}

void AprgWebCrawler::crawlOneHtmlAndOneFileToDownload(string& webLink, int const minimumSizeOfDownload)
{
    cout << "AprgWebCrawler::crawlPerHtmlAndDownloadImage" << endl;

    while(1)
    {
        AlbaWebPathHandler currentWebLinkPathHandler;
        currentWebLinkPathHandler.inputPath(webLink);
        AlbaWindowsPathHandler downloadPathHandler;
        downloadPathHandler.inputPath(m_workingPathHandler.getDirectory() + R"(\temp.html)");
        downloadUntilSuccessful<ConfigType::LowSpeedLimitAndMozillaFireFox>(currentWebLinkPathHandler, downloadPathHandler);
        LinksForHtmlAndFileToDownload links(getLinksBasedOnMode(currentWebLinkPathHandler, downloadPathHandler.getFullPath()));
        if(links.isInvalid())
        {
            cout << "Links are invalid." << endl;
            links.printLinks();
            return;
        }
        AlbaWebPathHandler fileToDownloadWebPathHandler(currentWebLinkPathHandler);
        fileToDownloadWebPathHandler.gotoLink(links.linkForCurrentFileToDownload);
        if(!fileToDownloadWebPathHandler.isFile())
        {
            cout << "Link is not to a file." << endl;
            cout << "Link of file to Download: " << fileToDownloadWebPathHandler.getFullPath() << endl;
            return;
        }
        downloadPathHandler.inputPath(links.localPathForCurrentFileToDownload);
        downloadPathHandler.createDirectoriesIfItDoesNotExist();
        downloadBinaryFileWithFiniteNumberOfTries<ConfigType::LowSpeedLimitAndMozillaFireFoxAndPrintDownloadProgress>(fileToDownloadWebPathHandler, downloadPathHandler, 20);
        if(downloadPathHandler.getFileSizeEstimate() < minimumSizeOfDownload)
        {
            cout << "Download file size is less than minimum. Retrying from the start." << endl;
            continue;
        }
        if(links.linkForNextHtml.empty())
        {
            cout << "Terminating the because next web link is empty." << endl;
            return;
        }
        AlbaWebPathHandler nextWebPathHandler(currentWebLinkPathHandler);
        nextWebPathHandler.gotoLink(links.linkForNextHtml);
        if(currentWebLinkPathHandler.getFullPath() == nextWebPathHandler.getFullPath())
        {
            cout << "Crawler stop because the next web link is the same as previous link." << endl;
            return;
        }
        webLink = nextWebPathHandler.getFullPath();
        saveMemoryCard();
    }
}

LinksForHtmlAndFileToDownload AprgWebCrawler::getLinksBasedOnMode(AlbaWebPathHandler const& webLinkPathHandler, string const& pathOfHtmlFile) const
{
    switch(m_mode)
    {
    case CrawlerMode::Gehen:
        return getLinksForGehen(webLinkPathHandler, pathOfHtmlFile);
    case CrawlerMode::GuroManga:
        return getLinksForGuroManga(webLinkPathHandler, pathOfHtmlFile);
    case CrawlerMode::HBrowse:
        return getLinksForHBrowse(webLinkPathHandler, pathOfHtmlFile);
    case CrawlerMode::Hentai2Read:
        return getLinksForHentai2Read(webLinkPathHandler, pathOfHtmlFile);
    case CrawlerMode::Mangafox:
        return getLinksForMangaFox(webLinkPathHandler, pathOfHtmlFile);
    case CrawlerMode::MangafoxWithVolume:        return getLinksForMangaFoxSaveInVolumeAndChapter(webLinkPathHandler, pathOfHtmlFile);
    case CrawlerMode::Mangahere:
        return getLinksForMangaHere(webLinkPathHandler, pathOfHtmlFile);
    case CrawlerMode::MangaPark:
        return getLinksForMangaPark(webLinkPathHandler, pathOfHtmlFile);
    case CrawlerMode::Y8:
        return getLinksForY8(webLinkPathHandler, pathOfHtmlFile);
    case CrawlerMode::ChiaAnime:    case CrawlerMode::Youtube:
        cout << "AprgWebCrawler::getLinks | Mode is not recognized" << endl;
        break;
    }    return LinksForHtmlAndFileToDownload();
}

}
