#include "WebCrawler.hpp"

#include <AlbaFileReader.hpp>
#include <AlbaStringHelper.hpp>
#include <CrawlConfiguration/CrawlConfiguration.hpp>
#include <fstream>
#include <iostream>

using namespace alba;
using namespace alba::stringHelper;
using namespace std;

namespace aprgWebCrawler
{

void WebCrawler::crawlForChiaAnime()
{
    for(string & webLink : m_webLinks)
    {
        crawlForChiaAnime(webLink);
    }
}

void WebCrawler::crawlForChiaAnime(string & webLink)
{
    cout << "WebCrawler::crawlForChiaAnime" << endl;
    CrawlConfiguration configuration(m_mode);
    while(!isCrawlStateInvalid())
    {
        AlbaWebPathHandler webPathHandler(webLink);
        LinksForChiaAnime links(getLinksForChiaAnime(webPathHandler));
        if(links.isInvalid())
        {
            cout << "Links are invalid." << endl;
            links.printLinks();
            saveStateToMemoryCard(CrawlState::LinksAreInvalid);
            break;
        }
        AlbaWebPathHandler videoWebPathHandler(webPathHandler);
        videoWebPathHandler.gotoLink(links.linkForDownloadPage);
        videoWebPathHandler.gotoLink(links.linkForCurrentVideo);
        if(!videoWebPathHandler.isFile())
        {
            cout << "Video link is not to a file." << endl;
            cout << "VideoLinkWebPath : " << videoWebPathHandler.getFullPath() << endl;
            saveStateToMemoryCard(CrawlState::DownloadedFileIsInvalid);
            break;
        }
        AlbaWindowsPathHandler downloadPathHandler(links.localPathForCurrentVideo);
        downloadPathHandler.createDirectoriesIfItDoesNotExist();
        if(!downloadBinaryFile(videoWebPathHandler, downloadPathHandler))
        {
            cout << "Download fails repetitively. Retrying from the start" << endl;
            continue;
        }
        if(downloadPathHandler.getFileSizeEstimate() < configuration.getMinimumFileSize())
        {
            cout << "Video file is less than "<<configuration.getMinimumFileSize()<<". FileSize = "<< downloadPathHandler.getFileSizeEstimate() <<" Invalid file. Retrying from the start" << endl;
            saveStateToMemoryCard(CrawlState::DownloadedFileSizeIsLessThanExpected);
            continue;
        }
        if(links.linkForNextHtml.empty())
        {
            cout << "Terminating the because next web link is empty." << endl;
            saveStateToMemoryCard(CrawlState::NextLinkIsInvalid);
            break;
        }
        AlbaWebPathHandler nextWebPathHandler(webPathHandler);
        nextWebPathHandler.gotoLink(links.linkForNextHtml);
        if(webPathHandler.getFullPath() == nextWebPathHandler.getFullPath())
        {
            cout << "Terminating the because next web link is the same as previous link." << endl;
            saveStateToMemoryCard(CrawlState::NextLinkIsInvalid);
            break;
        }
        webLink = nextWebPathHandler.getFullPath();
        setCrawlState(CrawlState::Active);
        saveMemoryCard();
    }
}

LinksForChiaAnime WebCrawler::getLinksForChiaAnime(AlbaWebPathHandler const& webLinkPathHandler) const
{
    LinksForChiaAnime links;
    AlbaWindowsPathHandler downloadPathHandler(m_downloadDirectoryPathHandler.getDirectory() + R"(\temp.html)");
    downloadFileAsText(webLinkPathHandler, downloadPathHandler);
    ifstream htmlFileStream(downloadPathHandler.getFullPath());
    if(!htmlFileStream.is_open())
    {
        cout << "Cannot open html file." << endl;
        cout << "File to read:" << downloadPathHandler.getFullPath() << endl;
        return links;
    }
    AlbaFileReader htmlFileReader(htmlFileStream);
    while (htmlFileReader.isNotFinished())
    {
        string lineInHtmlFile(htmlFileReader.simpleGetLine());
        if(isStringFoundInsideTheOtherStringCaseSensitive(lineInHtmlFile, R"(<a id="download")"))
        {
            links.linkForDownloadPage = getStringInBetweenTwoStrings(lineInHtmlFile, R"(href=")", R"(")");
        }
        else if(isStringFoundInsideTheOtherStringCaseSensitive(lineInHtmlFile, R"(>Next Episode<)"))
        {
            links.linkForNextHtml = getStringInBetweenTwoStrings(lineInHtmlFile, R"(<a href=")", R"(")");
        }
    }
    links.linkForCurrentVideo = getVideoLinkForChiaAnime(webLinkPathHandler, links.linkForDownloadPage);
    AlbaWebPathHandler videoWebPathHandler(links.linkForCurrentVideo);
    links.localPathForCurrentVideo = m_downloadDirectoryPathHandler.getDirectory() + R"(\Video\)" + videoWebPathHandler.getFile();
    return links;
}

string WebCrawler::getVideoLinkForChiaAnime(AlbaWebPathHandler const& webLinkPathHandler, string const& linkToDownloadPage) const
{
    AlbaWindowsPathHandler downloadPathHandler(m_downloadDirectoryPathHandler.getDirectory() + R"(\temp.html)");
    AlbaWebPathHandler downloadPagePathHandler(webLinkPathHandler);
    downloadPagePathHandler.gotoLink(linkToDownloadPage);
    downloadFileAsText(downloadPagePathHandler, downloadPathHandler);
    ifstream htmlFileStream(downloadPathHandler.getFullPath());
    if(!htmlFileStream.is_open())
    {
        cout << "Cannot open html file." << endl;
        cout << "File to read:" << downloadPathHandler.getFullPath() << endl;
        return string("");
    }
    AlbaFileReader htmlFileReader(htmlFileStream);
    while (htmlFileReader.isNotFinished())
    {
        string lineInHtmlFile(htmlFileReader.simpleGetLine());
        if(isStringFoundInsideTheOtherStringCaseSensitive(lineInHtmlFile, R"( target="_blank" )") &&
                isStringFoundInsideTheOtherStringCaseSensitive(lineInHtmlFile, R"( download=")"))
        {
            string webLink1(getStringInBetweenTwoStrings(lineInHtmlFile, R"(href=")", R"(")"));
            string webLink2(getStringAfterThisString(lineInHtmlFile, R"(href=")"));
            if(webLink1.empty())
            {
                return webLink2;
            }
            return webLink1;
        }
    }
    return string("");
}

}
