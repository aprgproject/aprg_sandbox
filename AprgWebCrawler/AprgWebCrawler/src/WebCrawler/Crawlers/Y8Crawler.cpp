#include <AlbaFileReader.hpp>
#include <AlbaStringHelper.hpp>
#include <Crawlers/Y8Crawler.hpp>
#include <iostream>

using namespace alba;
using namespace alba::stringHelper;
using namespace std;

namespace aprgWebCrawler
{

Y8Crawler::Y8Crawler(WebCrawler & webCrawler)
    : m_webCrawler(webCrawler)
    , m_configuration(webCrawler.getCrawlMode())
{}

void Y8Crawler::crawl()
{
    cout << "Y8Crawler::crawl" << endl;
    for(int webLinkIndex=0; webLinkIndex<m_webCrawler.getNumberOfWebLinks(); webLinkIndex++)
    {
        if(!isStringFoundInsideTheOtherStringCaseSensitive(m_webCrawler.getWebLinkAtIndex(webLinkIndex), R"(/games/)"))
        {
            addWebLinksIfFound(webLinkIndex);
        }
        else
        {
            crawl(webLinkIndex);
        }
        m_webCrawler.removeWebLink(webLinkIndex);
        webLinkIndex=0;
        m_webCrawler.saveStateToMemoryCard(CrawlState::Active);
    }
}

void Y8Crawler::crawl(int webLinkIndex)
{
    while(!m_webCrawler.isCrawlStateInvalid())
    {
        AlbaWebPathHandler webLinkPathHandler(m_webCrawler.getWebLinkAtIndex(webLinkIndex));
        retrieveLinks(webLinkPathHandler);
        if(areLinksInvalid())
        {
            cout << "Links are invalid." << endl;
            printLinks();
            break;
        }
        AlbaWebPathHandler fileToDownloadWebPathHandler(webLinkPathHandler);
        fileToDownloadWebPathHandler.gotoLink(m_linkForCurrentFileToDownload);
        if(!fileToDownloadWebPathHandler.isFile())
        {
            cout << "Link is not to a file." << endl;
            cout << "Link of file to Download: " << fileToDownloadWebPathHandler.getFullPath() << endl;
            break;
        }
        AlbaWindowsPathHandler downloadPathHandler(m_localPathForCurrentFileToDownload);
        downloadPathHandler.createDirectoriesForNonExisitingDirectories();
        m_webCrawler.downloadBinaryFile(fileToDownloadWebPathHandler, downloadPathHandler);
    }
}

void Y8Crawler::addWebLinksIfFound(int webLinkIndex)
{
    AlbaWebPathHandler webLinkPathHandler(m_webCrawler.getWebLinkAtIndex(webLinkIndex));
    cout << "Y8Crawler::addWebLinksIfFound" << webLinkPathHandler.getFullPath() << endl;
    AlbaWindowsPathHandler downloadPathHandler(m_webCrawler.getDownloadDirectory() + R"(\temp.html)");
    m_webCrawler.downloadFileAsText(webLinkPathHandler, downloadPathHandler);
    ifstream htmlFileStream(downloadPathHandler.getFullPath());
    if(!htmlFileStream.is_open())
    {
        cout << "Cannot open html file." << endl;
        cout << "File to read:" << downloadPathHandler.getFullPath() << endl;
    }
    string webLinkFound;
    bool isInsideVideoBox(false);
    AlbaFileReader htmlFileReader(htmlFileStream);
    while (htmlFileReader.isNotFinished())
    {
        string lineInHtmlFile(htmlFileReader.simpleGetLine());
        if(isStringFoundInsideTheOtherStringCaseSensitive(lineInHtmlFile, R"(<div class="item thumb videobox")"))
        {
            isInsideVideoBox = true;
        }
        else if(isStringFoundInsideTheOtherStringCaseSensitive(lineInHtmlFile, R"(</div>)"))
        {
            isInsideVideoBox = false;
            if(!webLinkFound.empty())
            {
                cout<<"Add webLink:"<<webLinkFound<<endl;
                m_webCrawler.addWebLink(webLinkFound);
                webLinkFound.clear();
            }
        }
        else if(isInsideVideoBox && isStringFoundInsideTheOtherStringCaseSensitive(lineInHtmlFile, R"(<a href=")"))
        {
            webLinkFound = AlbaWebPathHandler(string(R"(http://www.y8.com/)") + getStringInBetweenTwoStrings(lineInHtmlFile, R"(<a href=")", R"(")")).getFullPath();
        }
    }
}

void Y8Crawler::retrieveLinks(AlbaWebPathHandler const& webLinkPathHandler)
{
    clearLinks();
    AlbaWindowsPathHandler downloadPathHandler(m_webCrawler.getDownloadDirectory() + R"(\temp.html)");
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
        if(isStringFoundInsideTheOtherStringCaseSensitive(lineInHtmlFile, R"(<a class="controls-button maximize-button-no-js" href=")"))
        {
            m_linkForCurrentFileToDownload = getStringInBetweenTwoStrings(lineInHtmlFile, R"(<a class="controls-button maximize-button-no-js" href=")", R"(")");
        }
    }
    AlbaWebPathHandler flashWebPathHandler(webLinkPathHandler);
    flashWebPathHandler.gotoLink(m_linkForCurrentFileToDownload);
    m_localPathForCurrentFileToDownload = m_webCrawler.getDownloadDirectory() + R"(\Games\)" + flashWebPathHandler.getFile();
    m_linkForNextHtml.clear();
}

void Y8Crawler::clearLinks()
{
    m_linkForNextHtml.clear();
    m_linkForCurrentFileToDownload.clear();
    m_localPathForCurrentFileToDownload.clear();
}

bool Y8Crawler::areLinksInvalid() const
{
    return m_linkForCurrentFileToDownload.empty() || m_localPathForCurrentFileToDownload.empty();
}

void Y8Crawler::printLinks() const
{
    cout << "LinkForNextHtml : " << m_linkForNextHtml << endl;
    cout << "LinkForCurrentFileToDownload : " << m_linkForCurrentFileToDownload << endl;
    cout << "LocalPathForCurrentFileToDownload : " << m_localPathForCurrentFileToDownload << endl;
}

}
