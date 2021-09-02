#pragma once

#include <PathHandlers/AlbaLocalPathHandler.hpp>
#include <PathHandlers/AlbaWebPathHandler.hpp>
#include <WebCrawler/CrawlConfiguration/CrawlConfiguration.hpp>
#include <WebCrawler/CrawlHelpers/AutomatedFirefoxBrowser.hpp>
#include <WebCrawler/WebCrawler.hpp>

#include <string>

namespace aprgWebCrawler
{

class GoogleImages
{
public:
    GoogleImages(WebCrawler & webCrawler);
    void crawl();

private:
    void crawl(unsigned int const webLinkIndex);
    bool checkIfGoogleImagesLink(alba::AlbaWebPathHandler const& webLinkPathHandler);
    void retrieveLinks(alba::AlbaWebPathHandler const& webLinkPathHandler);
    bool checkLinks();
    void downloadFile(alba::AlbaWebPathHandler const& webLinkPathHandler);
    void clearLinks();
    bool areLinksInvalid() const;
    void printLinks() const;
    WebCrawler & m_webCrawler;
    CrawlConfiguration m_configuration;
    std::string m_linkForVideo;
    std::string m_localPathForCurrentVideo;
};

}
