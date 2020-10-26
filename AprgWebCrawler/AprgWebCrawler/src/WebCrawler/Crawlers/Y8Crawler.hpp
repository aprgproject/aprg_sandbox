#pragma once

#include <CrawlConfiguration/CrawlConfiguration.hpp>
#include <PathHandlers/AlbaLocalPathHandler.hpp>
#include <PathHandlers/AlbaWebPathHandler.hpp>
#include <WebCrawler.hpp>

#include <string>

namespace aprgWebCrawler
{

class Y8Crawler
{
public:
    Y8Crawler(WebCrawler & webCrawler);
    void crawl();

private:
    void crawl(int webLinkIndex);
    void addWebLinksIfFound(int webLinkIndex);
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


