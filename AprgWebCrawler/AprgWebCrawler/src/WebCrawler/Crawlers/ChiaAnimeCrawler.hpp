#pragma once

#include <CrawlConfiguration/CrawlConfiguration.hpp>
#include <PathHandlers/AlbaLocalPathHandler.hpp>
#include <PathHandlers/AlbaWebPathHandler.hpp>
#include <WebCrawler.hpp>

#include <string>

namespace aprgWebCrawler
{

class ChiaAnimeCrawler
{
public:
    ChiaAnimeCrawler(WebCrawler & webCrawler);
    void crawl();

private:
    void crawl(int webLinkIndex);
    void retrieveLinks(alba::AlbaWebPathHandler const& webLinkPathHandler);
    std::string getVideoLink(alba::AlbaWebPathHandler const& webLinkPathHandler, std::string const& linkToDownloadPage) const;
    bool checkLinks();
    void downloadVideo(alba::AlbaWebPathHandler const& webLinkPathHandler);
    void gotoNextLink(alba::AlbaWebPathHandler const& webLinkPathHandler, int webLinkIndex);
    void clearLinks();
    bool areLinksInvalid() const;
    void printLinks() const;
    WebCrawler & m_webCrawler;
    CrawlConfiguration m_configuration;
    std::string m_linkForNextHtml;
    std::string m_linkForDownloadPage;
    std::string m_linkForCurrentVideo;
    std::string m_localPathForCurrentVideo;
};

}
