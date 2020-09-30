#include "AprgWebCrawler.hpp"

#include <AlbaFileReader.hpp>
#include <AlbaStringHelper.hpp>
#include <CurlInterface.hpp>
#include <fstream>
#include <iostream>

using namespace curl::CurlInterface;
using namespace std;

using alba::stringHelper::getStringInBetweenTwoStrings;
using alba::stringHelper::getStringAfterThisString;
using alba::stringHelper::isStringFoundInsideTheOtherStringCaseSensitive;

namespace alba
{

void AprgWebCrawler::crawlForChiaAnime()
{
    for(string & webLink : m_webLinks)
    {
        crawlForChiaAnime(webLink);
    }
}

void AprgWebCrawler::crawlForChiaAnime(string & webLink)
{
    cout << "AprgWebCrawler::crawlForChiaAnime" << endl;

    while(1)
    {
        AlbaWebPathHandler webPathHandler;
        webPathHandler.inputPath(webLink);
        LinksForChiaAnime links(getLinksForChiaAnime(webPathHandler));
        if(links.isInvalid())
        {
            cout << "Links are invalid." << endl;
            links.printLinks();
            return;
        }
        AlbaWebPathHandler videoWebPathHandler(webPathHandler);
        videoWebPathHandler.gotoLink(links.linkForDownloadPage);
        videoWebPathHandler.gotoLink(links.linkForCurrentVideo);
        if(!videoWebPathHandler.isFile())
        {
            cout << "Video link is not to a file." << endl;
            cout << "VideoLinkWebPath : " << videoWebPathHandler.getFullPath() << endl;
            return;
        }
        AlbaWindowsPathHandler downloadPathHandler;
        downloadPathHandler.inputPath(links.localPathForCurrentVideo);
        downloadPathHandler.createDirectoriesIfItDoesNotExist();
        if(!downloadBinaryFile<ConfigType::LowSpeedLimitAndMozillaFireFoxAndPrintDownloadProgress>(videoWebPathHandler, downloadPathHandler))
        {
            cout << "Download of video file failed, retrying from the start" << endl;
            continue;
        }
        if(1000000 > downloadPathHandler.getFileSizeEstimate())
        {
            cout << "Video file is less than 1 mb. FileSize = "<< downloadPathHandler.getFileSizeEstimate() <<" Invalid file. Retrying from the start" << endl;
            continue;
        }
        if(links.linkForNextHtml.empty())
        {
            cout << "Terminating the because next web link is empty." << endl;
            return;
        }
        AlbaWebPathHandler nextWebPathHandler(webPathHandler);
        nextWebPathHandler.gotoLink(links.linkForNextHtml);
        if(webPathHandler.getFullPath() == nextWebPathHandler.getFullPath())
        {
            cout << "Terminating the because next web link is the same as previous link." << endl;
            return;
        }
        webLink = nextWebPathHandler.getFullPath();
        saveMemoryCard();
    }
}

LinksForChiaAnime AprgWebCrawler::getLinksForChiaAnime(AlbaWebPathHandler const& webLinkPathHandler) const
{
    LinksForChiaAnime links;
    AlbaWindowsPathHandler downloadPathHandler;
    downloadPathHandler.inputPath(m_workingPathHandler.getDirectory() + R"(\temp.html)");
    downloadUntilSuccessful<ConfigType::LowSpeedLimitAndMozillaFireFox>(webLinkPathHandler, downloadPathHandler);
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
    AlbaWebPathHandler videoWebPathHandler;
    videoWebPathHandler.inputPath(links.linkForCurrentVideo);
    links.localPathForCurrentVideo = m_workingPathHandler.getDirectory() + R"(\Video\)" + videoWebPathHandler.getFile();
    return links;
}

string AprgWebCrawler::getVideoLinkForChiaAnime(AlbaWebPathHandler const& webLinkPathHandler, string const& linkToDownloadPage) const
{
    AlbaWindowsPathHandler downloadPathHandler;
    downloadPathHandler.inputPath(m_workingPathHandler.getDirectory() + R"(\temp.html)");
    AlbaWebPathHandler downloadPagePathHandler(webLinkPathHandler);
    downloadPagePathHandler.gotoLink(linkToDownloadPage);
    downloadUntilSuccessful<ConfigType::LowSpeedLimitAndMozillaFireFox>(downloadPagePathHandler, downloadPathHandler);
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
        if(isStringFoundInsideTheOtherStringCaseSensitive(lineInHtmlFile, R"(<a target="_blank" download=")"))
        {
            string url1(getStringInBetweenTwoStrings(lineInHtmlFile, R"(href=")", R"(")"));
            string url2(getStringAfterThisString(lineInHtmlFile, R"(href=")"));
            if(url1.empty())
            {
                return url2;
            }
            return url1;
        }
    }
    return string("");
}

}
