#pragma once

#include <PathHandlers/AlbaLocalPathHandler.hpp>
#include <PathHandlers/AlbaWebPathHandler.hpp>
#include <WebCrawler/CrawlConfiguration/CrawlConfiguration.hpp>
#include <WebCrawler/WebCrawler.hpp>

#include <string>

namespace aprgWebCrawler
{

class Y8Crawler
{
public:
    Y8Crawler(WebCrawler & webCrawler);
    void crawl();

private:
    void crawl(unsigned int const webLinkIndex);
    void addWebLinksIfFound(unsigned int const webLinkIndex);
    void retrieveLinks(alba::AlbaWebPathHandler const& webLinkPathHandler);
    bool checkLinks();
    void downloadFile(alba::AlbaWebPathHandler const& webLinkPathHandler);
    void clearLinks();
    bool areLinksInvalid() const;
    void printLinks() const;
    WebCrawler & m_webCrawler;
    CrawlConfiguration m_configuration;
    std::string m_linkForNextHtml;
    std::string m_linkForCurrentFileToDownload;
    std::string m_localPathForCurrentFileToDownload;
};

}
