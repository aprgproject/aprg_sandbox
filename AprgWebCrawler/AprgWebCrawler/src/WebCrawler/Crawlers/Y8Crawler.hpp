#pragma once

#include <CrawlConfiguration/CrawlConfiguration.hpp>
#include <PathHandlers/AlbaWebPathHandler.hpp>
#include <PathHandlers/AlbaWindowsPathHandler.hpp>
#include <string>
#include <WebCrawler.hpp>

namespace aprgWebCrawler
{

class Y8Crawler
{
public:
    Y8Crawler(WebCrawler & webCrawler);
    void crawl();

private:
    void crawl(std::string & webLink);
    void addWebLinksIfFound(WebCrawler::WebLinks & webLinks, alba::AlbaWebPathHandler const& webLinkPathHandler);
    void retrieveLinks(alba::AlbaWebPathHandler const& webLinkPathHandler);
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
