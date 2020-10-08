#pragma once

#include <AlbaWebPathHandler.hpp>
#include <AlbaWindowsPathHandler.hpp>
#include <deque>
#include <fstream>
#include "LinksStructures/LinksStructures.hpp"
#include <string>

using std::deque;
using std::ofstream;
using std::string;

namespace alba
{

enum class CrawlerMode
{
    ChiaAnime,
    Gehen,
    GuroManga,
    Mangafox,
    MangafoxWithVolume,
    Mangahere,
    Y8,
    Youtube
};

class AprgWebCrawler
{

public:
    AprgWebCrawler(string const& workingDirectory);
    bool isValid() const;
    void printStatus() const;
    void saveMemoryCard() const;
    void loadMemoryCard();
    void crawl();

private:
    void setCrawlerMode(string const& modeString);
    string getCrawlerModeString() const;
    bool isWebLinksEmpty() const;
    bool isWebLinksValid() const;
    string saveWebPageManuallyUsingMozillaFirefoxAndGetLocalPath(AlbaWebPathHandler const& webPathHandler) const;

    void crawlOneHtmlAndOneFileToDownload();
    void crawlOneHtmlAndOneFileToDownload(string& webLink);
    LinksForHtmlAndFileToDownload getLinksBasedOnMode(AlbaWebPathHandler const& webLinkPathHandler, string const& pathOfHtmlFile) const;
    LinksForHtmlAndFileToDownload getLinksForGuroManga(AlbaWebPathHandler const& webLinkPathHandler, string const& pathOfHtmlFile) const;
    LinksForHtmlAndFileToDownload getLinksForMangaFox(AlbaWebPathHandler const& webLinkPathHandler, string const& pathOfHtmlFile) const;
    LinksForHtmlAndFileToDownload getLinksForMangaFoxSaveInVolumeAndChapter(AlbaWebPathHandler const& webLinkPathHandler, string const& pathOfHtmlFile) const;
    LinksForHtmlAndFileToDownload getNextLinkAndImageLinkForMangaFox(string const& pathOfHtmlFile) const;
    LinksForHtmlAndFileToDownload getLinksForMangaHere(AlbaWebPathHandler const& webLinkPathHandler, string const& pathOfHtmlFile) const;
    LinksForHtmlAndFileToDownload getLinksForGehen(AlbaWebPathHandler const& webLinkPathHandler, string const& pathOfHtmlFile) const;
    LinksForHtmlAndFileToDownload getLinksForY8(AlbaWebPathHandler const& webLinkPathHandler, string const& pathOfHtmlFile) const;

    void saveImageListFromGoogleImages();
    void downloadGoogleImages() const;

    void crawlForChiaAnime();
    void crawlForChiaAnime(string& webLink);
    LinksForChiaAnime getLinksForChiaAnime(AlbaWebPathHandler const& webLinkPathHandler) const;
    string getVideoLinkForChiaAnime(AlbaWebPathHandler const& webLinkPathHandler, string const& linkToDownloadPage) const;

    void crawlForYoutube();
    void crawlForYoutube(string& webLink, ofstream& convertedYoutubeLinkStream);
    LinksForYoutube getLinksForYoutube(AlbaWebPathHandler const& webLinkPathHandler) const;

    bool m_isModeRecognized;
    CrawlerMode m_mode;
    deque<string> m_webLinks;
    AlbaWindowsPathHandler m_workingPathHandler;
    AlbaWindowsPathHandler m_memoryCardPathHandler;
};

}
