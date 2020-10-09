#include "AprgWebCrawler.hpp"

#include <AlbaFileReader.hpp>
#include <AlbaStringHelper.hpp>
#include <CurlInterface.hpp>
#include <fstream>
#include <iostream>

using namespace curl::CurlInterface;
using namespace std;

using alba::stringHelper::getStringAfterThisString;
using alba::stringHelper::getStringAndReplaceNonAlphanumericCharactersToUnderScore;
using alba::stringHelper::getStringInBetweenTwoStrings;
using alba::stringHelper::getStringWithUrlDecodedString;
using alba::stringHelper::isStringFoundInsideTheOtherStringCaseSensitive;
using alba::stringHelper::isStringFoundInsideTheOtherStringNotCaseSensitive;

namespace alba
{

void AprgWebCrawler::crawlForYoutube()
{
    AlbaWindowsPathHandler convertedYoutubeLinksPathHandler;
    convertedYoutubeLinksPathHandler.inputPath(m_workingPathHandler.getDirectory() + R"(\ConvertedYoutubeLinks.txt)");
    convertedYoutubeLinksPathHandler.createDirectoriesIfItDoesNotExist();
    ofstream convertedYoutubeLinkStream(convertedYoutubeLinksPathHandler.getFullPath());

    for(string & webLink : m_webLinks)
    {
        crawlForYoutube(webLink, convertedYoutubeLinkStream);
    }
}

void AprgWebCrawler::crawlForYoutube(string & webLink, ofstream& convertedYoutubeLinkStream)
{
    cout << "AprgWebCrawler::crawlForYoutube" << endl;

    while(1)
    {
        if(!isStringFoundInsideTheOtherStringNotCaseSensitive(webLink, "youtube"))
        {
            cout << "Not a youtube link : " << webLink << endl;
            return;
        }
        AlbaWebPathHandler webPathHandler;
        webPathHandler.inputPath(webLink);
        LinksForYoutube links(getLinkForYoutube(webPathHandler));
        if(links.isInvalid())
        {
            cout << "Links are invalid." << endl;
            links.printLinks();
            continue;
        }
        AlbaWebPathHandler videoWebPathHandler;
        videoWebPathHandler.inputPath(links.linkForVideo);
        AlbaWindowsPathHandler downloadPathHandler;
        downloadPathHandler.inputPath(links.localPathForCurrentVideo);
        downloadPathHandler.createDirectoriesIfItDoesNotExist();
        if(!downloadBinaryFileWithFiniteNumberOfTries<ConfigType::LowSpeedLimitAndMozillaFireFoxAndPrintDownloadProgress>(videoWebPathHandler, downloadPathHandler, 10))
        {
            cout << "Download of video file failed, retrying from the start" << endl;
            continue;
        }
        convertedYoutubeLinkStream << links.linkForVideo << endl << flush;
        webLink.clear();
        saveMemoryCard();
        break;
    }
}

LinksForYoutube AprgWebCrawler::getLinkForYoutube(AlbaWebPathHandler const& webLinkPathHandler) const
{
    LinksForYoutube links;
    AlbaWebPathHandler ssYoutubeLinkPathHandler;
    string ssYoutubeLink(webLinkPathHandler.getFullPath());
    stringHelper::transformReplaceStringIfFound(ssYoutubeLink, "youtube", "ssyoutube");
    ssYoutubeLinkPathHandler.inputPath(ssYoutubeLink);
    string linkForVideo(getLinkManuallyUsingMozillaFirefox(ssYoutubeLinkPathHandler));

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
    links.localPathForCurrentVideo = m_workingPathHandler.getDirectory() + R"(\Video\)" + fileNameForVideo + ".mp4";
    return links;
}

}
