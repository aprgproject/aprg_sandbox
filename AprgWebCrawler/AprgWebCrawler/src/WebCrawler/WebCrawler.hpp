#pragma once

#include <deque>
#include <fstream>
#include <CrawlMode.hpp>
#include <CrawlState.hpp>
#include <PathHandlers/AlbaWebPathHandler.hpp>
#include <PathHandlers/AlbaWindowsPathHandler.hpp>
#include <string>

namespace aprgWebCrawler
{

class WebCrawler
{
public:
    typedef std::deque<std::string> WebLinks;
    WebCrawler(std::string const& downloadDirectory);
    WebCrawler(std::string const& workingDirectory, std::string const& webLink);

    void crawl();

    CrawlMode getCrawlMode() const;
    CrawlState getCrawlState() const;
    std::string getCrawlModeString() const;
    std::string getCrawlStateString() const;
    std::string getDownloadDirectory() const;
    std::string getNewDirectoryName() const;
    std::string getNewDirectoryNameFromWeblink(std::string const& webLink) const;
    std::string getFirstWebLinkIfPossible() const;
    std::string getTemporaryFilePath() const;

    int getNumberOfWebLinks();
    std::string getWebLinkAtIndex(int index);
    void addWebLink(std::string const& webLink);
    void modifyWebLink(std::string const& webLink, int index);
    void removeWebLink(int index);

    bool isValid() const;
    bool shouldDownloadStopBaseOnInvalidCrawlState() const;
    bool shouldDownloadRestartBaseOnCrawlState() const;
    bool isCurrentDownloadFinishedBaseOnCrawlState() const;

    void saveMemoryCard() const;
    void saveStateToMemoryCard(CrawlState state);
    void loadMemoryCard();

    void printStatus() const;

private:
    std::string getTitleFromTitleWindow(std::string const& webLink) const;
    bool isModeUnrecognized() const;
    bool isWebLinksEmpty() const;
    bool isWebLinksValid() const;
    void setCrawlMode(CrawlMode mode);
    void setCrawlState(CrawlState state);

    CrawlMode convertStringToCrawlerMode(std::string const& modeString) const;
    CrawlMode convertWebLinkToCrawlerMode(std::string const& webLink) const;
    CrawlState convertStringToCrawlerState(std::string const& stateString) const;
    std::string convertCrawlerModeToString(CrawlMode mode) const;
    std::string convertCrawlerStateToString(CrawlState state) const;

    CrawlMode m_mode;
    CrawlState m_state;
    alba::AlbaWindowsPathHandler m_downloadDirectoryPathHandler;
    alba::AlbaWindowsPathHandler m_memoryCardPathHandler;
    WebLinks m_webLinks;
};

}
