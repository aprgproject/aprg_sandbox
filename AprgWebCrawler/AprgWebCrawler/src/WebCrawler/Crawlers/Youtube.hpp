#pragma once

#include <CrawlConfiguration/CrawlConfiguration.hpp>
#include <CrawlHelpers/AutomationHelper.hpp>
#include <PathHandlers/AlbaWebPathHandler.hpp>
#include <PathHandlers/AlbaWindowsPathHandler.hpp>
#include <string>
#include <WebCrawler.hpp>

namespace aprgWebCrawler
{

class Youtube
{
public:
    Youtube(WebCrawler & webCrawler);
    void crawl();

private:
    void crawl(int webLinkIndex);
    bool checkIfYoutubeLink(alba::AlbaWebPathHandler const& webLinkPathHandler);
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
    AutomationHelper m_automationHelper;
};

}
