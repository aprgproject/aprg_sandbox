#include <File/AlbaFileReader.hpp>
#include <String/AlbaStringHelper.hpp>
#include <Crawlers/DoujinMoeCrawler.hpp>
#include <CrawlHelpers/Downloaders.hpp>
#include <iostream>

using namespace alba;
using namespace alba::stringHelper;
using namespace aprgWebCrawler::Downloaders;
using namespace std;

namespace aprgWebCrawler
{

DoujinMoeCrawler::DoujinMoeCrawler(WebCrawler & webCrawler)
    : m_webCrawler(webCrawler)
    , m_configuration(webCrawler.getCrawlMode())
{}

void DoujinMoeCrawler::crawl()
{
    cout << "DoujinMoeCrawler::crawl" << endl;
    for(int webLinkIndex=0; webLinkIndex<m_webCrawler.getNumberOfWebLinks();)
    {
        crawl(webLinkIndex);
        if(!m_innerLinks.empty())
        {
            for(string const& innerLink : m_innerLinks)
            {
                m_webCrawler.addWebLink(innerLink);
            }
        }
        if(m_webCrawler.isOnInvalidCrawlState())
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

void DoujinMoeCrawler::crawl(int webLinkIndex)
{
    while(!m_webCrawler.isOnInvalidCrawlState())
    {
        m_webCrawler.saveStateToMemoryCard(CrawlState::Active);
        AlbaWebPathHandler webLinkPathHandler(m_webCrawler.getWebLinkAtIndex(webLinkIndex));
        retrieveLinks(webLinkPathHandler);
        if(checkLinks())
        {
            if(!m_innerLinks.empty())
            {
                cout << "Inner links found, adding to webLinks first" << endl;
                break;
            }
            downloadImages(webLinkPathHandler);
        }
        if(m_webCrawler.isOnCrawlStatesWhichRetryIsNeeded())
        {
            continue;
        }
        if(m_webCrawler.isOnCurrentDownloadFinishedCrawlState())
        {
            break;
        }
    }
}

void DoujinMoeCrawler::retrieveLinks(AlbaWebPathHandler const& webLinkPathHandler)
{
    clearLinks();
    AlbaWindowsPathHandler downloadPathHandler(m_webCrawler.getDownloadDirectory() + R"(\temp.html)");
    downloadFileAsText(webLinkPathHandler, downloadPathHandler);
    ifstream htmlFileStream(downloadPathHandler.getFullPath());
    if(!htmlFileStream.is_open())
    {
        cout << "Cannot open html file." << endl;
        cout << "File to read:" << downloadPathHandler.getFullPath() << endl;
    }
    else
    {
        int state=0;
        AlbaFileReader htmlFileReader(htmlFileStream);
        while (htmlFileReader.isNotFinished())
        {
            string lineInHtmlFile(htmlFileReader.simpleGetLine());
            if(isStringFoundInsideTheOtherStringCaseSensitive(lineInHtmlFile, R"(<title>)"))
            {
                m_title = getStringAndReplaceNonAlphanumericCharactersToUnderScore(getStringInBetweenTwoStrings(lineInHtmlFile, R"(<title>)", R"(</title>)"));
            }
            else if(isStringFoundInsideTheOtherStringCaseSensitive(lineInHtmlFile, R"(<div id="dircontent">)"))
            {
                state=1;
            }
            else if(isStringFoundInsideTheOtherStringCaseSensitive(lineInHtmlFile, R"(<div id="gallery")"))
            {
                state=2;
            }
            else if(isStringFoundInsideTheOtherStringCaseSensitive(lineInHtmlFile, R"(<div class="controlbar">)"))
            {
                state=3;
            }
            if(1==state)
            {
                if(isStringFoundInsideTheOtherStringCaseSensitive(lineInHtmlFile, R"(<a href=")"))
                {
                    AlbaWebPathHandler innerLink(webLinkPathHandler);
                    innerLink.gotoLink(getStringInBetweenTwoStrings(lineInHtmlFile, R"(<a href=")", R"(")"));
                    m_innerLinks.emplace_back(innerLink.getFullPath());
                }
            }
            else if(2==state)
            {
                if(isStringFoundInsideTheOtherStringCaseSensitive(lineInHtmlFile, R"(<djm file=")"))
                {
                    AlbaWebPathHandler imageLink(webLinkPathHandler);
                    imageLink.gotoLink(getStringInBetweenTwoStrings(lineInHtmlFile, R"(<djm file=")", R"(")"));
                    m_imageLinks.emplace_back(imageLink.getFullPath());
                }
            }
        }
    }
}

bool DoujinMoeCrawler::checkLinks()
{
    bool result(true);
    if(areLinksInvalid())
    {
        cout << "Links are invalid." << endl;
        m_webCrawler.saveStateToMemoryCard(CrawlState::LinksAreInvalid);
        result = false;
    }
    return result;
}

void DoujinMoeCrawler::downloadImages(AlbaWebPathHandler const& webLinkPathHandler)
{
    NumberToStringConverter converter;
    converter.setFillCharacter('0');
    converter.setFieldWidth(5);
    int count = 0;
    for(string const& imageLink : m_imageLinks)
    {
        AlbaWebPathHandler imageWebPathHandler(webLinkPathHandler);
        imageWebPathHandler.gotoLink(imageLink);
        if(!imageWebPathHandler.isFile())
        {
            cout << "Image link is not to a file." << endl;
            cout << "ImageWebPath : " << imageWebPathHandler.getFullPath() << endl;
            m_webCrawler.saveStateToMemoryCard(CrawlState::DownloadedFileIsInvalid);
            return;
        }
        AlbaWindowsPathHandler downloadPathHandler(m_webCrawler.getDownloadDirectory() + R"(\)" + m_title + R"(\)" + converter.convert(count) + "." + imageWebPathHandler.getExtension());
        downloadPathHandler.createDirectoriesForNonExisitingDirectories();
        if(!downloadBinaryFile(imageWebPathHandler, downloadPathHandler, m_webCrawler.getCrawlMode()))
        {
            cout << "Download fails repetitively. Retrying from the start" << endl;
            m_webCrawler.saveStateToMemoryCard(CrawlState::DownloadFailsAndRetryIsNeeded);
            return;
        }
        if(downloadPathHandler.getFileSizeEstimate() < m_configuration.getMinimumFileSize())
        {
            cout << "Image file is less than " << m_configuration.getMinimumFileSize() << ". FileSize = " << downloadPathHandler.getFileSizeEstimate() << " Invalid file. Retrying from the start" << endl;
            m_webCrawler.saveStateToMemoryCard(CrawlState::DownloadedFileSizeIsLessThanExpected);
            return;
        }
        count++;
    }
    m_webCrawler.saveStateToMemoryCard(CrawlState::CurrentDownloadIsFinished);
}

void DoujinMoeCrawler::clearLinks()
{
    m_title.clear();
    m_innerLinks.clear();
    m_imageLinks.clear();
}

bool DoujinMoeCrawler::areLinksInvalid() const
{
    return (m_innerLinks.empty() && m_imageLinks.empty()) || m_title.empty();
}

}
