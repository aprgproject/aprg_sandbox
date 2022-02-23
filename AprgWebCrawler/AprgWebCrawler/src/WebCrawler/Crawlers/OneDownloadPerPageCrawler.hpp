#pragma once

#include <Common/PathHandler/AlbaLocalPathHandler.hpp>
#include <Common/PathHandler/AlbaWebPathHandler.hpp>
#include <WebCrawler/CrawlConfiguration/CrawlConfiguration.hpp>
#include <WebCrawler/CrawlMode.hpp>
#include <WebCrawler/WebCrawler.hpp>

#include <string>

namespace aprgWebCrawler
{

class OneDownloadPerPageCrawler
{
public:
    OneDownloadPerPageCrawler(WebCrawler & webCrawler);
    void crawl();

private:
    void crawl(unsigned int const webLinkIndex);
    void retrieveLinks(alba::AlbaWebPathHandler const& webLinkPathHandler);
    void retrieveLinksForGehen(alba::AlbaWebPathHandler const& webLinkPathHandler);
    void retrieveLinksForGuroManga(alba::AlbaWebPathHandler const& webLinkPathHandler);
    void retrieveLinksForHBrowse(alba::AlbaWebPathHandler const& webLinkPathHandler);
    void retrieveLinksForH2Read(alba::AlbaWebPathHandler const& webLinkPathHandler);
    void retrieveLinksForMangaFox(alba::AlbaWebPathHandler const& webLinkPathHandler);
    void retrieveLinksForMangaFoxSaveInVolumeAndChapter(alba::AlbaWebPathHandler const& webLinkPathHandler);
    void retrieveNextLinkAndImageLinkForMangaFox(alba::AlbaWebPathHandler const& webLinkPathHandler);
    void retrieveLinksForMangaHere(alba::AlbaWebPathHandler const& webLinkPathHandler);
    void retrieveLinksForMangaPark(alba::AlbaWebPathHandler const& webLinkPathHandler);
    bool checkLinks();
    void downloadFile(alba::AlbaWebPathHandler const& webLinkPathHandler);
    void gotoNextLink(alba::AlbaWebPathHandler const& webLinkPathHandler, unsigned int const webLinkIndex);
    void clearLinks();
    bool areLinksInvalid() const;
    void printLinks() const;
    WebCrawler & m_webCrawler;
    CrawlConfiguration m_configuration;
    CrawlMode m_mode;
    std::string m_linkForNextHtml;
    std::string m_linkForCurrentFileToDownload;
    std::string m_localPathForCurrentFileToDownload;
};

}
