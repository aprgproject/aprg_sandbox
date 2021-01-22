#pragma once

#include <CrawlConfiguration/CrawlConfiguration.hpp>
#include <CrawlHelpers/AutomatedFirefoxBrowser.hpp>
#include <PathHandlers/AlbaLocalPathHandler.hpp>
#include <PathHandlers/AlbaWebPathHandler.hpp>
#include <WebCrawler.hpp>

#include <string>

namespace aprgWebCrawler
{

class GoogleImages
{
public:
    GoogleImages(WebCrawler & webCrawler);
    void crawl();

private:
    void crawl(int webLinkIndex);
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
    AutomatedFirefoxBrowser m_automatedFirefoxBrowser;
};

}
