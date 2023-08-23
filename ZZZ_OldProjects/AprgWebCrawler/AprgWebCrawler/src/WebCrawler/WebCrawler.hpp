#pragma once

#include <Common/PathHandler/AlbaLocalPathHandler.hpp>
#include <Common/PathHandler/AlbaWebPathHandler.hpp>
#include <WebCrawler/CrawlMode.hpp>
#include <WebCrawler/CrawlState.hpp>

#include <deque>
#include <fstream>
#include <string>

namespace aprgWebCrawler {

class WebCrawler {
public:
    typedef std::deque<std::string> WebLinks;
    WebCrawler(std::string const& downloadDirectory, std::string const& temporaryFilePath);
    WebCrawler(std::string const& workingDirectory, std::string const& webLink, std::string const& temporaryFilePath);

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
    void setTemporaryFilePath(std::string const& temporaryFilePath);

    unsigned int getNumberOfWebLinks();
    std::string getWebLinkAtIndex(int index);
    void addWebLink(std::string const& webLink);
    void modifyWebLink(std::string const& webLink, int index);
    void removeWebLink(int index);

    bool isValid() const;
    bool isOnInvalidCrawlState() const;
    bool isOnCrawlStatesWhichRetryIsNeeded() const;
    bool isOnCurrentDownloadFinishedCrawlState() const;

    void saveMemoryCard() const;
    void saveStateToMemoryCard(CrawlState const state);
    void loadMemoryCard();
    void saveImportantLink(std::string const& link) const;

    void printStatus() const;

private:
    bool isModeUnrecognized() const;
    bool isWebLinksEmpty() const;
    bool isWebLinksValid() const;
    void setCrawlMode(CrawlMode const mode);
    void setCrawlState(CrawlState const state);

    CrawlMode convertStringToCrawlerMode(std::string const& modeString) const;
    CrawlMode convertWebLinkToCrawlerMode(std::string const& webLink) const;
    CrawlState convertStringToCrawlerState(std::string const& stateString) const;
    std::string convertCrawlerModeToString(CrawlMode const mode) const;
    std::string convertCrawlerStateToString(CrawlState const state) const;

    CrawlMode m_mode;
    CrawlState m_state;
    std::string m_temporaryFilePath;
    alba::AlbaLocalPathHandler m_downloadDirectoryPathHandler;
    alba::AlbaLocalPathHandler m_memoryCardPathHandler;
    alba::AlbaLocalPathHandler m_importantLinksPathHandler;
    WebLinks m_webLinks;
};

}  // namespace aprgWebCrawler
