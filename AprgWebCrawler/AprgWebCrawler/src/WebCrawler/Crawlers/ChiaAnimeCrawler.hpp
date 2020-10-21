#pragma once

#include <CrawlConfiguration/CrawlConfiguration.hpp>
#include <PathHandlers/AlbaWebPathHandler.hpp>
#include <PathHandlers/AlbaWindowsPathHandler.hpp>
#include <string>
#include <WebCrawler.hpp>

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
