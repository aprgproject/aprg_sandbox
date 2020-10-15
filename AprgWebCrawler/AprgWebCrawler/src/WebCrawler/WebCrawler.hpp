#pragma once

#include <deque>
#include <fstream>
#include <CrawlMode.hpp>
#include <CrawlState.hpp>
#include <LinksStructures/LinksForChiaAnime.hpp>
#include <LinksStructures/LinksForHtmlAndFileToDownload.hpp>
#include <LinksStructures/LinksForYoutube.hpp>
#include <PathHandlers/AlbaWebPathHandler.hpp>
#include <PathHandlers/AlbaWindowsPathHandler.hpp>
#include <string>

namespace aprgWebCrawler
{

class WebCrawler{
public:
    typedef std::deque<std::string> WebLinks;
    WebCrawler(std::string const& workingDirectory);
    bool isValid() const;
    void printStatus() const;
    CrawlMode getCrawlMode() const;
    CrawlState getCrawlState() const;
    std::string getCrawlModeString() const;
    std::string getCrawlStateString() const;
    void saveMemoryCard() const;
    void loadMemoryCard();
    void crawl();
private:
    void setCrawlMode(CrawlMode mode);
    void setCrawlState(CrawlState state);
    void saveInvalidStateToMemoryCard(CrawlState state);
    CrawlMode convertStringToCrawlerMode(std::string const& modeString) const;
    CrawlState convertStringToCrawlerState(std::string const& stateString) const;
    bool isCrawlStateInvalid() const;
    bool isWebLinksEmpty() const;
    bool isWebLinksValid() const;
    std::string getUserInputAfterManuallyUsingMozillaFirefox(alba::AlbaWebPathHandler const& webPathHandler) const;
    void gotoLinkManuallyUsingMozillaFirefox(alba::AlbaWebPathHandler const& webPathHandler) const;

    bool downloadBinaryFile(alba::AlbaWebPathHandler const& fileToDownloadWebPathHandler, alba::AlbaWindowsPathHandler const& downloadPathHandler) const;
    bool downloadFileAsText(alba::AlbaWebPathHandler const& fileToDownloadWebPathHandler, alba::AlbaWindowsPathHandler const& downloadPathHandler) const;

    void crawlOneHtmlAndOneFileToDownload();
    void crawlOneHtmlAndOneFileToDownload(std::string & webLink);
    LinksForHtmlAndFileToDownload getLinks(alba::AlbaWebPathHandler const& webLinkPathHandler, std::string const& pathOfHtmlFile) const;
    LinksForHtmlAndFileToDownload getLinksForGuroManga(alba::AlbaWebPathHandler const& webLinkPathHandler, std::string const& pathOfHtmlFile) const;
    LinksForHtmlAndFileToDownload getLinksForHBrowse(alba::AlbaWebPathHandler const& webLinkPathHandler, std::string const& pathOfHtmlFile) const;
    LinksForHtmlAndFileToDownload getLinksForHentai2Read(alba::AlbaWebPathHandler const& webLinkPathHandler, std::string const& pathOfHtmlFile) const;
    LinksForHtmlAndFileToDownload getLinksForMangaFox(alba::AlbaWebPathHandler const& webLinkPathHandler, std::string const& pathOfHtmlFile) const;
    LinksForHtmlAndFileToDownload getLinksForMangaFoxSaveInVolumeAndChapter(alba::AlbaWebPathHandler const& webLinkPathHandler, std::string const& pathOfHtmlFile) const;
    LinksForHtmlAndFileToDownload getNextLinkAndImageLinkForMangaFox(std::string const& pathOfHtmlFile) const;
    LinksForHtmlAndFileToDownload getLinksForMangaHere(alba::AlbaWebPathHandler const& webLinkPathHandler, std::string const& pathOfHtmlFile) const;
    LinksForHtmlAndFileToDownload getLinksForMangaPark(alba::AlbaWebPathHandler const& webLinkPathHandler, std::string const& pathOfHtmlFile) const;
    LinksForHtmlAndFileToDownload getLinksForGehen(alba::AlbaWebPathHandler const& webLinkPathHandler, std::string const& pathOfHtmlFile) const;
    LinksForHtmlAndFileToDownload getLinksForY8(alba::AlbaWebPathHandler const& webLinkPathHandler, std::string const& pathOfHtmlFile) const;

    void saveImageListFromGoogleImages();
    void downloadGoogleImages() const;
    void crawlForChiaAnime();
    void crawlForChiaAnime(std::string & webLink);
    LinksForChiaAnime getLinksForChiaAnime(alba::AlbaWebPathHandler const& webLinkPathHandler) const;
    std::string getVideoLinkForChiaAnime(alba::AlbaWebPathHandler const& webLinkPathHandler, std::string const& linkToDownloadPage) const;

    void crawlForYoutube();
    void crawlForYoutube(std::string & webLink, std::ofstream & convertedYoutubeLinkStream);
    void crawlForYoutube_Old(std::string & webLink, std::ofstream & convertedYoutubeLinkStream);
    LinksForYoutube getLinkForYoutube(alba::AlbaWebPathHandler const& webLinkPathHandler) const;

    alba::AlbaWindowsPathHandler m_workingPathHandler;
    alba::AlbaWindowsPathHandler m_memoryCardPathHandler;
    bool m_isModeRecognized;
    CrawlMode m_mode;
    CrawlState m_state;    WebLinks m_webLinks;
};

}