#include <AlbaFileReader.hpp>
#include <AlbaStringHelper.hpp>
#include <Crawlers/ChiaAnimeCrawler.hpp>
#include <iostream>

using namespace alba;
using namespace alba::stringHelper;
using namespace std;

namespace aprgWebCrawler
{

ChiaAnimeCrawler::ChiaAnimeCrawler(WebCrawler & webCrawler)
    : m_webCrawler(webCrawler)
    , m_configuration(webCrawler.getCrawlMode())
{}

void ChiaAnimeCrawler::crawl()
{
    cout << "ChiaAnimeCrawler::crawl" << endl;
    for(int webLinkIndex=0; webLinkIndex<m_webCrawler.getNumberOfWebLinks(); webLinkIndex++)
    {
        crawl(webLinkIndex);
    }
}

void ChiaAnimeCrawler::crawl(int webLinkIndex)
{
    while(!m_webCrawler.isCrawlStateInvalid())
    {
        AlbaWebPathHandler webLinkPathHandler(m_webCrawler.getWebLinkAtIndex(webLinkIndex));
        retrieveLinks(webLinkPathHandler);
        if(areLinksInvalid())
        {
            cout << "Links are invalid." << endl;            printLinks();
            m_webCrawler.saveStateToMemoryCard(CrawlState::LinksAreInvalid);
            break;
        }
        AlbaWebPathHandler videoWebPathHandler(webLinkPathHandler);
        videoWebPathHandler.gotoLink(m_linkForDownloadPage);
        videoWebPathHandler.gotoLink(m_linkForCurrentVideo);
        if(!videoWebPathHandler.isFile())        {
            cout << "Video link is not to a file." << endl;
            cout << "VideoLinkWebPath : " << videoWebPathHandler.getFullPath() << endl;
            m_webCrawler.saveStateToMemoryCard(CrawlState::DownloadedFileIsInvalid);            break;
        }
        AlbaWindowsPathHandler downloadPathHandler(m_localPathForCurrentVideo);
        downloadPathHandler.createDirectoriesForNonExisitingDirectories();
        if(!m_webCrawler.downloadBinaryFile(videoWebPathHandler, downloadPathHandler))
        {
            cout << "Download fails repetitively. Retrying from the start" << endl;
            continue;
        }
        if(downloadPathHandler.getFileSizeEstimate() < m_configuration.getMinimumFileSize())
        {
            cout << "Video file is less than " << m_configuration.getMinimumFileSize() << ". FileSize = " << downloadPathHandler.getFileSizeEstimate() << " Invalid file. Retrying from the start" << endl;
            m_webCrawler.saveStateToMemoryCard(CrawlState::DownloadedFileSizeIsLessThanExpected);
            continue;
        }
        if(m_linkForNextHtml.empty())
        {
            cout << "Terminating the because next web link is empty." << endl;
            m_webCrawler.saveStateToMemoryCard(CrawlState::NextLinkIsInvalid);
            break;
        }
        AlbaWebPathHandler nextWebPathHandler(webLinkPathHandler);
        nextWebPathHandler.gotoLink(m_linkForNextHtml);
        if(webLinkPathHandler.getFullPath() == nextWebPathHandler.getFullPath())
        {
            cout << "Terminating the because next web link is the same as previous link." << endl;
            m_webCrawler.saveStateToMemoryCard(CrawlState::NextLinkIsInvalid);
            break;
        }
        m_webCrawler.modifyWebLink(nextWebPathHandler.getFullPath(), webLinkIndex);
        m_webCrawler.saveStateToMemoryCard(CrawlState::Active);
    }
}
void ChiaAnimeCrawler::retrieveLinks(AlbaWebPathHandler const& webLinkPathHandler)
{
    clearLinks();    AlbaWindowsPathHandler downloadPathHandler(m_webCrawler.getDownloadDirectory() + R"(\temp.html)");
    m_webCrawler.downloadFileAsText(webLinkPathHandler, downloadPathHandler);
    ifstream htmlFileStream(downloadPathHandler.getFullPath());
    if(!htmlFileStream.is_open())
    {
        cout << "Cannot open html file." << endl;
        cout << "File to read:" << downloadPathHandler.getFullPath() << endl;
    }
    AlbaFileReader htmlFileReader(htmlFileStream);
    while (htmlFileReader.isNotFinished())
    {
        string lineInHtmlFile(htmlFileReader.simpleGetLine());
        if(isStringFoundInsideTheOtherStringCaseSensitive(lineInHtmlFile, R"(<a id="download")"))
        {
            m_linkForDownloadPage = getStringInBetweenTwoStrings(lineInHtmlFile, R"(href=")", R"(")");
        }
        else if(isStringFoundInsideTheOtherStringCaseSensitive(lineInHtmlFile, R"(>Next Episode<)"))
        {
            m_linkForNextHtml = getStringInBetweenTwoStrings(lineInHtmlFile, R"(<a href=")", R"(")");
        }
    }
    m_linkForCurrentVideo = getVideoLink(webLinkPathHandler, m_linkForDownloadPage);
    AlbaWebPathHandler videoWebPathHandler(m_linkForCurrentVideo);
    m_localPathForCurrentVideo = m_webCrawler.getDownloadDirectory() + R"(\Video\)" + videoWebPathHandler.getFile();
}

string ChiaAnimeCrawler::getVideoLink(AlbaWebPathHandler const& webLinkPathHandler, string const& linkToDownloadPage) const
{
    AlbaWindowsPathHandler downloadPathHandler(m_webCrawler.getDownloadDirectory() + R"(\temp.html)");
    AlbaWebPathHandler downloadPagePathHandler(webLinkPathHandler);
    downloadPagePathHandler.gotoLink(linkToDownloadPage);
    m_webCrawler.downloadFileAsText(downloadPagePathHandler, downloadPathHandler);
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

void ChiaAnimeCrawler::clearLinks()
{
    m_linkForNextHtml.clear();
    m_linkForDownloadPage.clear();
    m_linkForCurrentVideo.clear();
    m_localPathForCurrentVideo.clear();
}

bool ChiaAnimeCrawler::areLinksInvalid() const
{
    return m_linkForDownloadPage.empty() || m_linkForCurrentVideo.empty() || m_localPathForCurrentVideo.empty();
}

void ChiaAnimeCrawler::printLinks() const
{
    cout << "LinkForNextHtml : " << m_linkForNextHtml << endl;
    cout << "LinkForDownloadPage : " << m_linkForDownloadPage << endl;
    cout << "LinkForCurrentVideo : " << m_linkForCurrentVideo << endl;
    cout << "LocalPathForCurrentVideo : " << m_localPathForCurrentVideo << endl;
}

}
