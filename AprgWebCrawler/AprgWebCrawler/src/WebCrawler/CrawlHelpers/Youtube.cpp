#include "WebCrawler.hpp"

#include <AlbaFileReader.hpp>
#include <AlbaStringHelper.hpp>
#include <fstream>
#include <iostream>

using namespace alba;
using namespace alba::stringHelper;
using namespace std;

namespace aprgWebCrawler
{

void WebCrawler::crawlForYoutube()
{
    AlbaWindowsPathHandler convertedYoutubeLinksPathHandler(m_downloadDirectoryPathHandler.getDirectory() + R"(\ConvertedYoutubeLinks.txt)");
    convertedYoutubeLinksPathHandler.createDirectoriesIfItDoesNotExist();
    ofstream convertedYoutubeLinkStream(convertedYoutubeLinksPathHandler.getFullPath());

    for(string & webLink : m_webLinks)
    {
        crawlForYoutube(webLink, convertedYoutubeLinkStream);
    }
}

void WebCrawler::crawlForYoutube(string & webLink, ofstream& convertedYoutubeLinkStream)
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
        string userInput(getUserInputAfterManuallyUsingMozillaFirefox(ssYoutubeLinkPathHandler));
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

void WebCrawler::crawlForYoutube_Old(string & webLink, ofstream& convertedYoutubeLinkStream)
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
        AlbaWebPathHandler webPathHandler(webLink);
        LinksForYoutube links(getLinkForYoutube(webPathHandler));
        if(links.isInvalid())
        {
            cout << "Links are invalid." << endl;
            links.printLinks();
            continue;
        }
        AlbaWebPathHandler videoWebPathHandler(links.linkForVideo);
        AlbaWindowsPathHandler downloadPathHandler(links.localPathForCurrentVideo);
        downloadPathHandler.createDirectoriesIfItDoesNotExist();
        downloadBinaryFile(videoWebPathHandler, downloadPathHandler);
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
    string linkForVideo(getUserInputAfterManuallyUsingMozillaFirefox(ssYoutubeLinkPathHandler));

    string fileNameForVideo1(getStringInBetweenTwoStrings(linkForVideo, "&title=", "&"));
    string fileNameForVideo2(getStringAfterThisString(linkForVideo, "&title="));
    string fileNameForVideo("NoName");
    if((!fileNameForVideo1.empty()))
    {
        fileNameForVideo = fileNameForVideo1;
    }
    else if((!fileNameForVideo2.empty()))
    {
        fileNameForVideo = fileNameForVideo2;
    }

    fileNameForVideo = getStringAndReplaceNonAlphanumericCharactersToUnderScore(
                getStringWithUrlDecodedString(fileNameForVideo));
    links.linkForVideo = linkForVideo;
    links.localPathForCurrentVideo = m_downloadDirectoryPathHandler.getDirectory() + R"(\Video\)" + fileNameForVideo + ".mp4";
    return links;
}

}
