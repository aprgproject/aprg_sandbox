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

namespace alba
{

class WebCrawler
{
public:
    typedef std::deque<std::string> WebLinks;
    WebCrawler(std::string const& workingDirectory);
    bool isValid() const;
    void printStatus() const;
    void saveMemoryCard() const;    void loadMemoryCard();
    void crawl();

private:
    void setCrawlerMode(CrawlMode mode);
    void setCrawlerState(CrawlState state);
    void saveInvalidStateToMemoryCard(CrawlState state);
    std::string getCrawlerMode() const;
    std::string getCrawlerState() const;
    CrawlMode convertStringToCrawlerMode(std::string const& modeString) const;
    CrawlState convertStringToCrawlerState(std::string const& stateString) const;
    bool isCrawlStateInvalid() const;
    bool isWebLinksEmpty() const;
    bool isWebLinksValid() const;
    std::string getUserInputAfterManuallyUsingMozillaFirefox(AlbaWebPathHandler const& webPathHandler) const;
    void gotoLinkManuallyUsingMozillaFirefox(AlbaWebPathHandler const& webPathHandler) const;

    bool downloadBinaryFile(AlbaWebPathHandler const& fileToDownloadWebPathHandler, AlbaWindowsPathHandler const& downloadPathHandler) const;
    bool downloadFileAsText(AlbaWebPathHandler const& fileToDownloadWebPathHandler, AlbaWindowsPathHandler const& downloadPathHandler) const;

    void crawlOneHtmlAndOneFileToDownload();
    void crawlOneHtmlAndOneFileToDownload(std::string & webLink);
    LinksForHtmlAndFileToDownload getLinks(AlbaWebPathHandler const& webLinkPathHandler, std::string const& pathOfHtmlFile) const;
    LinksForHtmlAndFileToDownload getLinksForGuroManga(AlbaWebPathHandler const& webLinkPathHandler, std::string const& pathOfHtmlFile) const;
    LinksForHtmlAndFileToDownload getLinksForHBrowse(AlbaWebPathHandler const& webLinkPathHandler, std::string const& pathOfHtmlFile) const;
    LinksForHtmlAndFileToDownload getLinksForHentai2Read(AlbaWebPathHandler const& webLinkPathHandler, std::string const& pathOfHtmlFile) const;
    LinksForHtmlAndFileToDownload getLinksForMangaFox(AlbaWebPathHandler const& webLinkPathHandler, std::string const& pathOfHtmlFile) const;
    LinksForHtmlAndFileToDownload getLinksForMangaFoxSaveInVolumeAndChapter(AlbaWebPathHandler const& webLinkPathHandler, std::string const& pathOfHtmlFile) const;
    LinksForHtmlAndFileToDownload getNextLinkAndImageLinkForMangaFox(std::string const& pathOfHtmlFile) const;
    LinksForHtmlAndFileToDownload getLinksForMangaHere(AlbaWebPathHandler const& webLinkPathHandler, std::string const& pathOfHtmlFile) const;
    LinksForHtmlAndFileToDownload getLinksForMangaPark(AlbaWebPathHandler const& webLinkPathHandler, std::string const& pathOfHtmlFile) const;
    LinksForHtmlAndFileToDownload getLinksForGehen(AlbaWebPathHandler const& webLinkPathHandler, std::string const& pathOfHtmlFile) const;
    LinksForHtmlAndFileToDownload getLinksForY8(AlbaWebPathHandler const& webLinkPathHandler, std::string const& pathOfHtmlFile) const;

    void saveImageListFromGoogleImages();
    void downloadGoogleImages() const;

    void crawlForChiaAnime();
    void crawlForChiaAnime(std::string & webLink);
    LinksForChiaAnime getLinksForChiaAnime(AlbaWebPathHandler const& webLinkPathHandler) const;
    std::string getVideoLinkForChiaAnime(AlbaWebPathHandler const& webLinkPathHandler, std::string const& linkToDownloadPage) const;

    void crawlForYoutube();
    void crawlForYoutube(std::string & webLink, std::ofstream & convertedYoutubeLinkStream);
    void crawlForYoutube_Old(std::string & webLink, std::ofstream & convertedYoutubeLinkStream);
    LinksForYoutube getLinkForYoutube(AlbaWebPathHandler const& webLinkPathHandler) const;

    AlbaWindowsPathHandler m_workingPathHandler;
    AlbaWindowsPathHandler m_memoryCardPathHandler;
    bool m_isModeRecognized;
    CrawlMode m_mode;
    CrawlState m_state;
    WebLinks m_webLinks;
};

}
