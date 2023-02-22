#include <Common/File/AlbaFileReader.hpp>
#include <Common/String/AlbaStringHelper.hpp>
#include <WebCrawler/CrawlConfiguration/CrawlConfiguration.hpp>
#include <WebCrawler/WebCrawler.hpp>

#include <fstream>
#include <iostream>

using namespace alba;
using namespace alba::stringHelper;
using namespace std;

/*
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
    cout << "WebCrawler::crawlForYoutube\n";
    while(!isCrawlStateInvalid())
    {
        if(!isStringFoundInsideTheOtherStringNotCaseSensitive(webLink, "youtube"))
        {
            cout << "Not a youtube link : " << webLink << "\n";
            saveStateToMemoryCard(CrawlState::LinksAreInvalid);
            break;
        }
        string ssYoutubeLink(webLink);
        stringHelper::transformReplaceStringIfFound(ssYoutubeLink, "ssyoutube", "youtube");
        stringHelper::transformReplaceStringIfFound(ssYoutubeLink, "youtube", "ssyoutube");
        AlbaWebPathHandler ssYoutubeLinkPathHandler(ssYoutubeLink);
        cout<<"Enter user input(done, retry):\n";
        //string userInput(getUserInputAfterManuallyUsingMozillaFirefox(ssYoutubeLinkPathHandler));
        if(!stringHelper::isEqualNotCaseSensitive(userInput, "done"))
        {
            continue;
        }
        convertedYoutubeLinkStream << ssYoutubeLinkPathHandler.getFullPath() << "\n" << flush;
        webLink.clear();
        setCrawlState(CrawlState::Active);
        saveMemoryCard();
        break;
    }
}

void WebCrawler::crawlForYoutube(string & webLink, ofstream& convertedYoutubeLinkStream)
{
    cout << "WebCrawler::crawlForYoutube\n";
    CrawlConfiguration configuration(m_mode);
    while(!isCrawlStateInvalid())
    {
        if(!isStringFoundInsideTheOtherStringNotCaseSensitive(webLink, "youtube"))
        {
            cout << "Not a youtube link : " << webLink << "\n";
            saveStateToMemoryCard(CrawlState::LinksAreInvalid);
            break;
        }
        AlbaWebPathHandler webPathHandler(webLink);
        LinksForYoutube links(getLinkForYoutube(webPathHandler));
        if(links.isInvalid())
        {
            cout << "Links are invalid.\n";
            links.printLinks();
            continue;
        }
        AlbaWebPathHandler videoWebPathHandler(links.linkForVideo);
        AlbaLocalPathHandler downloadPathHandler(links.localPathForCurrentVideo);
        downloadPathHandler.createDirectoriesForNonExisitingDirectories();
        downloadBinaryFile(videoWebPathHandler, downloadPathHandler);
        if(downloadPathHandler.getFileSizeEstimate() < configuration.getMinimumFileSize())
        {
            cout << "Video file is less than "<<configuration.getMinimumFileSize()<<". FileSize = "<< downloadPathHandler.getFileSizeEstimate() <<" Invalid file. Retrying from the start\n";
            saveStateToMemoryCard(CrawlState::DownloadedFileSizeIsLessThanExpected);
            continue;
        }
        convertedYoutubeLinkStream << links.linkForVideo << "\n" << flush;
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
        cout << "Cannot open html file.\n";
        cout << "File to read:" << downloadPathHandler.getFullPath() << "\n";
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
*/
