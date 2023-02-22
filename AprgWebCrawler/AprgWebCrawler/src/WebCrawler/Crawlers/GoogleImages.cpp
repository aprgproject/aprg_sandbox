#include <Common/File/AlbaFileReader.hpp>
#include <Common/String/AlbaStringHelper.hpp>
#include <WebCrawler/CrawlHelpers/Downloaders.hpp>
#include <WebCrawler/Crawlers/GoogleImages.hpp>

#include <windows.h>

#include <iostream>

using namespace alba;
using namespace alba::stringHelper;
using namespace aprgWebCrawler::Downloaders;
using namespace std;

namespace aprgWebCrawler
{

GoogleImages::GoogleImages(WebCrawler & webCrawler)
    : m_webCrawler(webCrawler)
    , m_configuration(webCrawler.getCrawlMode())
{}

void GoogleImages::crawl()
{
    cout << "GoogleImages::crawl\n";
    for(unsigned int webLinkIndex=0; webLinkIndex<m_webCrawler.getNumberOfWebLinks();)
    {
        crawl(webLinkIndex);
        if(m_webCrawler.isOnCurrentDownloadFinishedCrawlState())
        {
            m_webCrawler.removeWebLink(webLinkIndex);
            m_webCrawler.saveMemoryCard();
            webLinkIndex=0;
        }
        else
        {
            m_webCrawler.addWebLink(m_webCrawler.getWebLinkAtIndex(webLinkIndex));
            m_webCrawler.removeWebLink(webLinkIndex);
            m_webCrawler.saveMemoryCard();
            webLinkIndex=0;
        }
    }
}

void GoogleImages::crawl(unsigned int const webLinkIndex)
{
    m_webCrawler.saveStateToMemoryCard(CrawlState::Active);
    AlbaWebPathHandler webLinkPathHandler(m_webCrawler.getWebLinkAtIndex(webLinkIndex));
    if(checkIfGoogleImagesLink(webLinkPathHandler))
    {
        retrieveLinks(webLinkPathHandler);
        if(checkLinks())
        {
            downloadFile(webLinkPathHandler);
        }
    }
}

bool GoogleImages::checkIfGoogleImagesLink(AlbaWebPathHandler const& webLinkPathHandler)
{
    bool result(true);
    if(!isStringFoundInsideTheOtherStringNotCaseSensitive(webLinkPathHandler.getFullPath(), "youtube"))
    {
        cout << "Not a youtube link : " << webLinkPathHandler.getFullPath() << "\n";
        m_webCrawler.saveStateToMemoryCard(CrawlState::LinksAreInvalid);
        result = false;
    }
    return result;
}

void GoogleImages::retrieveLinks(AlbaWebPathHandler const& webLinkPathHandler)
{
    clearLinks();
    string ssGoogleImagesLink(webLinkPathHandler.getFullPath());
    stringHelper::transformReplaceStringIfFound(ssGoogleImagesLink, "youtube", "ssyoutube");
    AlbaWebPathHandler ssGoogleImagesLinkPathHandler(ssGoogleImagesLink);
    AlbaLocalPathHandler downloadPathHandler(m_webCrawler.getTemporaryFilePath());
    downloadPathHandler.deleteFile();
    AutomatedFirefoxBrowser::getInstance().downloadFileWithDefaultSettings(ssGoogleImagesLinkPathHandler.getFullPath(), downloadPathHandler.getFullPath());
    ifstream htmlFileStream(downloadPathHandler.getFullPath());
    if(!htmlFileStream.is_open())
    {
        cout << "Cannot open html file.\n";
        cout << "File to read:" << downloadPathHandler.getFullPath() << "\n";
    }
    else
    {
        AlbaFileReader htmlFileReader(htmlFileStream);
        int isDownloadFound(false);
        while (htmlFileReader.isNotFinished())
        {
            string lineInHtmlFile(htmlFileReader.getLine());
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

bool GoogleImages::checkLinks()
{
    bool result(true);
    if(areLinksInvalid())
    {
        cout << "Links are invalid. Retrying to retrieve links\n";
        printLinks();
        m_webCrawler.saveStateToMemoryCard(CrawlState::LinksAreInvalid);
        result = false;
    }
    return result;
}

void GoogleImages::downloadFile(AlbaWebPathHandler const& webLinkPathHandler)
{
    AlbaWebPathHandler videoWebPathHandler(webLinkPathHandler);
    videoWebPathHandler.gotoLink(m_linkForVideo);
    AlbaLocalPathHandler temporaryPath(m_webCrawler.getTemporaryFilePath());
    ListOfPaths files;
    ListOfPaths directories;
    temporaryPath.input(temporaryPath.getDirectory());
    temporaryPath.findFilesAndDirectoriesOneDepth("*.*", files, directories);
    unsigned int initialNumberOfFiles(files.size());
    //AutomatedFirefoxBrowser::getInstance().downloadLinkUsingMozillaFirefoxAndFdm(videoWebPathHandler.getFullPath());
    temporaryPath.findFilesAndDirectoriesOneDepth("*.*", files, directories);
    if(initialNumberOfFiles+1 == files.size())
    {
        cout << "Waiting for download to finish\n";
        bool isNotFinished(true);
        while(isNotFinished)
        {
            files.clear();
            directories.clear();
            temporaryPath.findFilesAndDirectoriesOneDepth("*.fdminc", files, directories);
            cout<<"\risNotFinished:"<<isNotFinished<<" numberOfIncompleteFiles:"<<files.size();
            isNotFinished = !files.empty();
            Sleep(10000);
        }
        m_webCrawler.saveStateToMemoryCard(CrawlState::CurrentDownloadIsFinished);
    }
    else
    {
        m_webCrawler.saveStateToMemoryCard(CrawlState::DownloadFailsAndRetryIsNeeded);
    }
}

void GoogleImages::clearLinks()
{
    m_linkForVideo.clear();
    m_localPathForCurrentVideo.clear();
}

bool GoogleImages::areLinksInvalid() const
{
    return m_linkForVideo.empty() || m_localPathForCurrentVideo.empty();
}

void GoogleImages::printLinks() const
{
    cout << "m_linkForVideo : " << m_linkForVideo << "\n";
    cout << "m_localPathForCurrentVideo : " << m_localPathForCurrentVideo << "\n";
}

}
