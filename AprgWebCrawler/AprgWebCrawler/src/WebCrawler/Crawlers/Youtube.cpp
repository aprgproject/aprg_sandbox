#include <Common/File/AlbaFileReader.hpp>
#include <Common/String/AlbaStringHelper.hpp>
#include <WebCrawler/CrawlHelpers/Downloaders.hpp>
#include <WebCrawler/Crawlers/Youtube.hpp>

#include <windows.h>

#include <iostream>

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
    cout << "Youtube::crawl\n";
    for(unsigned int webLinkIndex=0; webLinkIndex<m_webCrawler.getNumberOfWebLinks();)
    {
        crawl(webLinkIndex);
        if(m_webCrawler.isOnCurrentDownloadFinishedCrawlState())
        {
            m_webCrawler.removeWebLink(webLinkIndex);
            m_webCrawler.saveMemoryCard();
        }
        else
        {
            m_webCrawler.addWebLink(m_webCrawler.getWebLinkAtIndex(webLinkIndex));
            m_webCrawler.removeWebLink(webLinkIndex); //fix interface
            m_webCrawler.saveMemoryCard();
        }
        webLinkIndex=0;
    }
}

void Youtube::crawl(unsigned int const webLinkIndex)
{
    m_webCrawler.saveStateToMemoryCard(CrawlState::Active);
    AlbaWebPathHandler webLinkPathHandler(m_webCrawler.getWebLinkAtIndex(webLinkIndex));
    if(isYoutubeLink(webLinkPathHandler))
    {
        downloadFile(webLinkPathHandler);
    }
}

bool Youtube::isYoutubeLink(AlbaWebPathHandler const& webLinkPathHandler)
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

void Youtube::downloadFile(AlbaWebPathHandler const& webLinkPathHandler)
{
    AutomatedFirefoxBrowser& firefoxBrowser(AutomatedFirefoxBrowser::getInstance());

    string ssYoutubeLink(webLinkPathHandler.getFullPath());
    stringHelper::transformReplaceStringIfFound(ssYoutubeLink, "youtube", "ssyoutube");
    AlbaWebPathHandler ssYoutubeLinkPathHandler(ssYoutubeLink);

    firefoxBrowser.createNewTab();
    firefoxBrowser.openWebPathOnCurrentTab(ssYoutubeLinkPathHandler.getFullPath());
    AlbaLocalPathHandler localPathOfDownload(m_webCrawler.getDownloadDirectory());

    firefoxBrowser.doLeftClickAt(MousePosition(952, 506));
    firefoxBrowser.sleep(10000);

    firefoxBrowser.saveBinaryFile(localPathOfDownload.getDirectory());
    firefoxBrowser.closeTab();
    //m_webCrawler.saveStateToMemoryCard(CrawlState::CurrentDownloadIsFinished);
    //m_webCrawler.saveStateToMemoryCard(CrawlState::DownloadFailsAndRetryIsNeeded);
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
    cout << "m_linkForVideo : " << m_linkForVideo << "\n";
    cout << "m_localPathForCurrentVideo : " << m_localPathForCurrentVideo << "\n";
}

}
