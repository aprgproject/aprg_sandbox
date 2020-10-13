#include "AprgWebCrawler.hpp"

#include <CurlInterface.hpp>
#include "CrawlerConfiguration.hpp"
#include <iostream>

using namespace curl::CurlInterface;using namespace std;

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

    CrawlerConfiguration crawlerConfiguration(m_mode);
    while(1)
    {
        AlbaWebPathHandler currentWebLinkPathHandler(webLink);
        AlbaWindowsPathHandler downloadPathHandler(m_workingPathHandler.getDirectory() + R"(\temp.html)");
        downloadUntilSuccessful<ConfigType::LowSpeedLimitAndMozillaFireFox>(currentWebLinkPathHandler, downloadPathHandler);
        LinksForHtmlAndFileToDownload links(getLinks(currentWebLinkPathHandler, downloadPathHandler.getFullPath()));
        if(links.isInvalid())
        {
            cout << "Links are invalid." << endl;            links.printLinks();
            return;
        }
        AlbaWebPathHandler fileToDownloadWebPathHandler(currentWebLinkPathHandler);        fileToDownloadWebPathHandler.gotoLink(links.linkForCurrentFileToDownload);
        if(!fileToDownloadWebPathHandler.isFile())
        {
            cout << "Link is not to a file." << endl;
            cout << "Link of file to Download: " << fileToDownloadWebPathHandler.getFullPath() << endl;
            return;
        }
        downloadPathHandler.input(links.localPathForCurrentFileToDownload);
        downloadPathHandler.createDirectoriesIfItDoesNotExist();
        if(crawlerConfiguration.isFileToBeDownloadUntilSuccessful())
        {
            downloadBinaryFileUntilSuccessful<ConfigType::LowSpeedLimitAndMozillaFireFoxAndPrintDownloadProgress>(fileToDownloadWebPathHandler, downloadPathHandler);
        }
        else
        {
            downloadBinaryFileWithFiniteNumberOfTries<ConfigType::LowSpeedLimitAndMozillaFireFoxAndPrintDownloadProgress>(fileToDownloadWebPathHandler, downloadPathHandler, crawlerConfiguration.getNumberOfRetries());
        }
        if(downloadPathHandler.getFileSizeEstimate() < crawlerConfiguration.getMinimumFileSize())
        {
            cout << "Download file size is less than "<<crawlerConfiguration.getMinimumFileSize()<<". FileSize = "<< downloadPathHandler.getFileSizeEstimate() <<" Invalid file. Retrying from the start" << endl;
            continue;
        }
        if(links.linkForNextHtml.empty())        {
            cout << "Terminating the because next web link is empty." << endl;
            return;
        }        AlbaWebPathHandler nextWebPathHandler(currentWebLinkPathHandler);
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
    }    return LinksForHtmlAndFileToDownload();
}

}