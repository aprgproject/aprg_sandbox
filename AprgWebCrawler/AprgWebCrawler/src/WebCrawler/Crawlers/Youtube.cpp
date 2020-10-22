#include <AlbaFileReader.hpp>
#include <AlbaStringHelper.hpp>
#include <Crawlers/Youtube.hpp>
#include <CrawlHelpers/Downloaders.hpp>
#include <CrawlHelpers/AutomationHelper.hpp>
#include <iostream>
#include <windows.h>

using namespace alba;
using namespace alba::stringHelper;
using namespace aprgWebCrawler::Downloaders;
using namespace std;

namespace aprgWebCrawler
{

Youtube::Youtube(WebCrawler & webCrawler)
    : m_webCrawler(webCrawler)
    , m_configuration(webCrawler.getCrawlMode())
{}

void Youtube::crawl()
{
    cout << "Youtube::crawl" << endl;
    for(int webLinkIndex=0; webLinkIndex<m_webCrawler.getNumberOfWebLinks();)
    {
        crawl(webLinkIndex);
        if(m_webCrawler.shouldDownloadStopBaseOnInvalidCrawlState())
        {
            break;
        }
        else
        {
            m_webCrawler.removeWebLink(webLinkIndex);
            m_webCrawler.saveMemoryCard();
            webLinkIndex=0;
        }
    }
}

void Youtube::crawl(int webLinkIndex)
{
    while(!m_webCrawler.shouldDownloadStopBaseOnInvalidCrawlState())
    {
        m_webCrawler.saveStateToMemoryCard(CrawlState::Active);
        AlbaWebPathHandler webLinkPathHandler(m_webCrawler.getWebLinkAtIndex(webLinkIndex));
        if(checkIfYoutubeLink(webLinkPathHandler))
        {
            retrieveLinks(webLinkPathHandler);
            if(checkLinks())
            {
                downloadFile(webLinkPathHandler);
            }
        }
        if(m_webCrawler.shouldDownloadRestartBaseOnCrawlState())
        {
            continue;
        }
        if(m_webCrawler.isCurrentDownloadFinishedBaseOnCrawlState())
        {
            break;
        }
    }
}

bool Youtube::checkIfYoutubeLink(AlbaWebPathHandler const& webLinkPathHandler)
{
    bool result(true);
    if(!isStringFoundInsideTheOtherStringNotCaseSensitive(webLinkPathHandler.getFullPath(), "youtube"))
    {
        cout << "Not a youtube link : " << webLinkPathHandler.getFullPath() << endl;
        m_webCrawler.saveStateToMemoryCard(CrawlState::LinksAreInvalid);
        result = false;
    }
    return result;
}

void Youtube::retrieveLinks(AlbaWebPathHandler const& webLinkPathHandler)
{
    clearLinks();
    string ssYoutubeLink(webLinkPathHandler.getFullPath());
    stringHelper::transformReplaceStringIfFound(ssYoutubeLink, "youtube", "ssyoutube");
    AlbaWebPathHandler ssYoutubeLinkPathHandler(ssYoutubeLink);
    AlbaWindowsPathHandler downloadPathHandler(m_webCrawler.getTemporaryFilePath());
    downloadPathHandler.deleteFile();
    AutomationHelper::saveWebPageManuallyUsingMozillaFirefox(ssYoutubeLinkPathHandler.getFullPath());
    ifstream htmlFileStream(downloadPathHandler.getFullPath());
    if(!htmlFileStream.is_open())
    {
        cout << "Cannot open html file." << endl;
        cout << "File to read:" << downloadPathHandler.getFullPath() << endl;
    }
    else
    {
        AlbaFileReader htmlFileReader(htmlFileStream);
        int isDownloadFound(false);
        while (htmlFileReader.isNotFinished())
        {
            string lineInHtmlFile(htmlFileReader.simpleGetLine());
            if(isStringFoundInsideTheOtherStringCaseSensitive(lineInHtmlFile, R"(Download)"))
            {
                isDownloadFound=true;
            }
            else if(isDownloadFound && isStringFoundInsideTheOtherStringCaseSensitive(lineInHtmlFile, R"(http:/)"))
            {
                m_linkForVideo = getStringWithoutOpeningClosingOperators(lineInHtmlFile, '<', '>');
                string fileName(getStringWithUrlDecodedString(getStringInBetweenTwoStrings(lineInHtmlFile, R"(title=")", R"(>)")));
                m_localPathForCurrentVideo = m_webCrawler.getDownloadDirectory() + R"(\Video\)" + fileName;
                break;
            }
        }
    }
}

bool Youtube::checkLinks()
{
    bool result(true);
    if(areLinksInvalid())
    {
        cout << "Links are invalid. Retryin" << endl;
        printLinks();
        result = false;
    }
    return result;
}

void Youtube::downloadFile(AlbaWebPathHandler const& webLinkPathHandler)
{
    AlbaWebPathHandler videoWebPathHandler(webLinkPathHandler);
    videoWebPathHandler.gotoLink(m_linkForVideo);
    AlbaWindowsPathHandler downloadPathHandler(m_localPathForCurrentVideo);
    downloadPathHandler.createDirectoriesForNonExisitingDirectories();
    AutomationHelper::downloadLinkUsingMozillaFirefoxAndFdm(videoWebPathHandler.getFullPath());
    cout << "Waitin for download to finis" << endl;
    bool isNotFinished(true);
    while(isNotFinished)
    {
        AlbaWindowsPathHandler temporaryPath(m_webCrawler.getTemporaryFilePath());
        temporaryPath.input(temporaryPath.getDirectory());
        AlbaWindowsPathHandler::ListOfPaths files;
        AlbaWindowsPathHandler::ListOfPaths directories;
        temporaryPath.findFilesAndDirectoriesOneDepth("*.fdminc", files, directories);
        isNotFinished = !files.empty();
        Sleep(10000);
    }
    /*downloadBinaryFile(videoWebPathHandler, downloadPathHandler, m_webCrawler.getCrawlMode());
    if(downloadPathHandler.getFileSizeEstimate() < m_configuration.getMinimumFileSize())
    {
        cout << "Download file size is less than " << m_configuration.getMinimumFileSize() << ". FileSize = " << downloadPathHandler.getFileSizeEstimate() << " Invalid file. Retrying from the start" << endl;
        m_webCrawler.saveStateToMemoryCard(CrawlState::DownloadedFileSizeIsLessThanExpected);
    }
    else
    {
        m_webCrawler.saveStateToMemoryCard(CrawlState::CurrentDownloadIsFinished);
    }*/
    m_webCrawler.saveStateToMemoryCard(CrawlState::CurrentDownloadIsFinished);
}

void Youtube::clearLinks()
{
    m_linkForVideo.clear();
    m_localPathForCurrentVideo.clear();
}

bool Youtube::areLinksInvalid() const
{
    return m_linkForVideo.empty() || m_localPathForCurrentVideo.empty();
}

void Youtube::printLinks() const
{
    cout << "m_linkForVideo : " << m_linkForVideo << endl;
    cout << "m_localPathForCurrentVideo : " << m_localPathForCurrentVideo << endl;
}

}
