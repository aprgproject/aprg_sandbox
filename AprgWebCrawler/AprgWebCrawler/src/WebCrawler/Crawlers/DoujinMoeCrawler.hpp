#pragma once

#include <CrawlConfiguration/CrawlConfiguration.hpp>
#include <PathHandlers/AlbaWebPathHandler.hpp>
#include <PathHandlers/AlbaLocalPathHandler.hpp>
#include <string>
#include <WebCrawler.hpp>
#include <vector>

namespace aprgWebCrawler
{

class DoujinMoeCrawler
{
public:
    DoujinMoeCrawler(WebCrawler & webCrawler);
    void crawl();

private:
    void crawl(int webLinkIndex);
    void retrieveLinks(alba::AlbaWebPathHandler const& webLinkPathHandler);
    std::string getVideoLink(alba::AlbaWebPathHandler const& webLinkPathHandler, std::string const& linkToDownloadPage) const;
    bool checkLinks();
    void downloadImages(alba::AlbaWebPathHandler const& webLinkPathHandler);
    void clearLinks();
    bool areLinksInvalid() const;
    WebCrawler & m_webCrawler;
    CrawlConfiguration m_configuration;
    std::string m_title;
    std::vector<std::string> m_innerLinks;
    std::vector<std::string> m_imageLinks;
};

}
