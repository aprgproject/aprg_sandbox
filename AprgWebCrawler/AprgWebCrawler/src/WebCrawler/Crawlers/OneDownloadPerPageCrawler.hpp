#pragma once

#include <CrawlConfiguration/CrawlConfiguration.hpp>
#include <CrawlMode.hpp>
#include <PathHandlers/AlbaWebPathHandler.hpp>
#include <PathHandlers/AlbaWindowsPathHandler.hpp>
#include <string>
#include <WebCrawler.hpp>

namespace aprgWebCrawler
{

class OneDownloadPerPageCrawler
{
public:
    OneDownloadPerPageCrawler(WebCrawler & webCrawler);
    void crawl();

private:
    void crawl(std::string & webLink);
    void download(alba::AlbaWebPathHandler webPathHandler);
    void retrieveLinks(alba::AlbaWebPathHandler const& webLinkPathHandler);
    void retrieveLinksForGehen(alba::AlbaWebPathHandler const& webLinkPathHandler);
    void retrieveLinksForGuroManga(alba::AlbaWebPathHandler const& webLinkPathHandler);
    void retrieveLinksForHBrowse(alba::AlbaWebPathHandler const& webLinkPathHandler);
    void retrieveLinksForHentai2Read(alba::AlbaWebPathHandler const& webLinkPathHandler);
    void retrieveLinksForMangaFox(alba::AlbaWebPathHandler const& webLinkPathHandler);
    void retrieveLinksForMangaFoxSaveInVolumeAndChapter(alba::AlbaWebPathHandler const& webLinkPathHandler);
    void retrieveNextLinkAndImageLinkForMangaFox(alba::AlbaWebPathHandler const& webLinkPathHandler);
    void retrieveLinksForMangaHere(alba::AlbaWebPathHandler const& webLinkPathHandler);
    void retrieveLinksForMangaPark(alba::AlbaWebPathHandler const& webLinkPathHandler);
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
