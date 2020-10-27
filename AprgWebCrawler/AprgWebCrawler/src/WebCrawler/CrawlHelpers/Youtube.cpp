#include "WebCrawler.hpp"

#include <CrawlConfiguration/CrawlConfiguration.hpp>
#include <File/AlbaFileReader.hpp>
#include <String/AlbaStringHelper.hpp>

#include <fstream>
#include <iostream>

using namespace alba;
using namespace alba::stringHelper;
using namespace std;

namespace aprgWebCrawler
{

void WebCrawler::crawlForYoutube()
{
    AlbaLocalPathHandler convertedYoutubeLinksPathHandler(m_downloadDirectoryPathHandler.getDirectory() + R"(\ConvertedYoutubeLinks.txt)");
    convertedYoutubeLinksPathHandler.createDirectoriesForNonExisitingDirectories();
    ofstream convertedYoutubeLinkStream(convertedYoutubeLinksPathHandler.getFullPath());

    for(string & webLink : m_webLinks)
    {
        crawlForYoutube(webLink, convertedYoutubeLinkStream);
    }
}

void WebCrawler::crawlForYoutube_old(string & webLink, ofstream& convertedYoutubeLinkStream)
{
    cout << "WebCrawler::crawlForYoutube" << endl;
    while(!isCrawlStateInvalid())
    {
        if(!isStringFoundInsideTheOtherStringNotCaseSensitive(webLink, "youtube"))
        {
            cout << "Not a youtube link : " << webLink << endl;
            saveStateToMemoryCard(CrawlState::LinksAreInvalid);
            break;
        }
        string ssYoutubeLink(webLink);
        stringHelper::transformReplaceStringIfFound(ssYoutubeLink, "ssyoutube", "youtube");
        stringHelper::transformReplaceStringIfFound(ssYoutubeLink, "youtube", "ssyoutube");
        AlbaWebPathHandler ssYoutubeLinkPathHandler(ssYoutubeLink);
        cout<<"Enter user input(done, retry):"<<endl;
        //string userInput(getUserInputAfterManuallyUsingMozillaFirefox(ssYoutubeLinkPathHandler));
        if(!stringHelper::isEqualNotCaseSensitive(userInput, "done"))
        {
            continue;
        }
        convertedYoutubeLinkStream << ssYoutubeLinkPathHandler.getFullPath() << endl << flush;
        webLink.clear();
        setCrawlState(CrawlState::Active);
        saveMemoryCard();
        break;
    }
}

void WebCrawler::crawlForYoutube(string & webLink, ofstream& convertedYoutubeLinkStream)
{
    cout << "WebCrawler::crawlForYoutube" << endl;
    CrawlConfiguration configuration(m_mode);
    while(!isCrawlStateInvalid())
    {
        if(!isStringFoundInsideTheOtherStringNotCaseSensitive(webLink, "youtube"))
        {
            cout << "Not a youtube link : " << webLink << endl;
            saveStateToMemoryCard(CrawlState::LinksAreInvalid);
            break;
        }
        AlbaWebPathHandler webPathHandler(webLink);
        LinksForYoutube links(getLinkForYoutube(webPathHandler));
        if(links.isInvalid())
        {
            cout << "Links are invalid." << endl;
            links.printLinks();
            continue;
        }
        AlbaWebPathHandler videoWebPathHandler(links.linkForVideo);
        AlbaLocalPathHandler downloadPathHandler(links.localPathForCurrentVideo);
        downloadPathHandler.createDirectoriesForNonExisitingDirectories();
        downloadBinaryFile(videoWebPathHandler, downloadPathHandler);
        if(downloadPathHandler.getFileSizeEstimate() < configuration.getMinimumFileSize())
        {
            cout << "Video file is less than "<<configuration.getMinimumFileSize()<<". FileSize = "<< downloadPathHandler.getFileSizeEstimate() <<" Invalid file. Retrying from the start" << endl;
            saveStateToMemoryCard(CrawlState::DownloadedFileSizeIsLessThanExpected);
            continue;
        }
        convertedYoutubeLinkStream << links.linkForVideo << endl << flush;
        webLink.clear();
        setCrawlState(CrawlState::Active);
        saveMemoryCard();
        break;
    }
}

LinksForYoutube WebCrawler::getLinkForYoutube(AlbaWebPathHandler const& webLinkPathHandler) const
{
    LinksForYoutube links;
    string ssYoutubeLink(webLinkPathHandler.getFullPath());
    stringHelper::transformReplaceStringIfFound(ssYoutubeLink, "youtube", "ssyoutube");
    AlbaWebPathHandler ssYoutubeLinkPathHandler(ssYoutubeLink);
    AlbaLocalPathHandler downloadPathHandler(m_downloadDirectoryPathHandler.getDirectory() + R"(\temp.html)");
    downloadFileUsingPhantomJs(ssYoutubeLinkPathHandler, downloadPathHandler);
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
        string lineInHtmlFile(htmlFileReader.getLine());
        if(isStringFoundInsideTheOtherStringCaseSensitive(lineInHtmlFile, R"(<div class="def-btn-box"><a)"))
        {
            links.linkForVideo = getStringInBetweenTwoStrings(lineInHtmlFile, R"(href=")", R"(")");
            links.localPathForCurrentVideo = m_downloadDirectoryPathHandler.getDirectory() + R"(\Video\)" + getStringInBetweenTwoStrings(lineInHtmlFile, R"(download=")", R"(")");
        }
    }
    return links;
}

}
