#pragma once

#include <deque>
#include <fstream>
#include "LinksStructures/LinksStructures.hpp"
#include <PathHandlers/AlbaWebPathHandler.hpp>
#include <PathHandlers/AlbaWindowsPathHandler.hpp>
#include <string>

namespace alba
{
enum class CrawlerMode
{
    ChiaAnime,    Gehen,
    GuroManga,
    HBrowse,
    Hentai2Read,
    Mangafox,
    MangafoxWithVolume,
    Mangahere,
    MangaPark,
    Y8,
    Youtube
};

class AprgWebCrawler
{
public:
    typedef std::deque<std::string> WebLinks;
    AprgWebCrawler(std::string const& workingDirectory);
    bool isValid() const;
    void printStatus() const;
    void saveMemoryCard() const;    void loadMemoryCard();
    void crawl();

private:
    void setCrawlerMode(std::string const& modeString);
    std::string getCrawlerModeString() const;
    bool isWebLinksEmpty() const;
    bool isWebLinksValid() const;
    std::string getUserInputAfterManuallyUsingMozillaFirefox(AlbaWebPathHandler const& webPathHandler) const;
    void gotoLinkManuallyUsingMozillaFirefox(AlbaWebPathHandler const& webPathHandler) const;

    void crawlOneHtmlAndOneFileToDownload(int const minimumSizeOfDownload);
    void crawlOneHtmlAndOneFileToDownload(string& webLink, int const minimumSizeOfDownload);
    LinksForHtmlAndFileToDownload getLinksBasedOnMode(AlbaWebPathHandler const& webLinkPathHandler, std::string const& pathOfHtmlFile) const;
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
    void crawlForChiaAnime(string& webLink);
    LinksForChiaAnime getLinksForChiaAnime(AlbaWebPathHandler const& webLinkPathHandler) const;
    std::string getVideoLinkForChiaAnime(AlbaWebPathHandler const& webLinkPathHandler, std::string const& linkToDownloadPage) const;

    void crawlForYoutube();
    void crawlForYoutube(string& webLink, std::ofstream & convertedYoutubeLinkStream);
    void crawlForYoutube_Old(string& webLink, std::ofstream & convertedYoutubeLinkStream);
    LinksForYoutube getLinkForYoutube(AlbaWebPathHandler const& webLinkPathHandler) const;

    AlbaWindowsPathHandler m_workingPathHandler;    AlbaWindowsPathHandler m_memoryCardPathHandler;
    bool m_isModeRecognized;
    CrawlerMode m_mode;
    WebLinks m_webLinks;
};

}