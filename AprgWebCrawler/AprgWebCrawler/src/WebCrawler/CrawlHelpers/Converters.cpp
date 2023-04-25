#include <Common/String/AlbaStringHelper.hpp>
#include <WebCrawler/WebCrawler.hpp>

using namespace alba::stringHelper;
using namespace std;

namespace aprgWebCrawler {

CrawlMode WebCrawler::convertStringToCrawlerMode(string const& modeString) const {
    CrawlMode mode(CrawlMode::Empty);
    if ("CrawlMode::Unknown" == modeString) {
        mode = CrawlMode::Unknown;
    } else if (
        "chiaanime" == modeString || "CrawlerMode::ChiaAnime" == modeString || "CrawlMode::ChiaAnime" == modeString) {
        mode = CrawlMode::ChiaAnime;
    } else if ("doujinmoe" == modeString || "CrawlMode::DoujinMoe" == modeString) {
        mode = CrawlMode::DoujinMoe;
    } else if ("gehen" == modeString || "CrawlerMode::Gehen" == modeString || "CrawlMode::Gehen" == modeString) {
        mode = CrawlMode::Gehen;
    } else if (
        "guromanga" == modeString || "CrawlerMode::GuroManga" == modeString || "CrawlMode::GuroManga" == modeString) {
        mode = CrawlMode::GuroManga;
    } else if ("hbrowse" == modeString || "CrawlerMode::HBrowse" == modeString || "CrawlMode::HBrowse" == modeString) {
        mode = CrawlMode::HBrowse;
    } else if ("h2read" == modeString || "CrawlerMode::H2Read" == modeString || "CrawlMode::H2Read" == modeString) {
        mode = CrawlMode::H2Read;
    } else if (
        "mangafox" == modeString || "CrawlerMode::Mangafox" == modeString || "CrawlMode::Mangafox" == modeString) {
        mode = CrawlMode::Mangafox;
    } else if (
        "mangafoxfullpath" == modeString || "CrawlerMode::MangafoxWithVolume" == modeString ||
        "CrawlMode::MangafoxWithVolume" == modeString) {
        mode = CrawlMode::MangafoxWithVolume;
    } else if (
        "mangahere" == modeString || "CrawlerMode::Mangahere" == modeString || "CrawlMode::Mangahere" == modeString) {
        mode = CrawlMode::Mangahere;
    } else if (
        "mangapark" == modeString || "CrawlerMode::MangaPark" == modeString || "CrawlMode::MangaPark" == modeString) {
        mode = CrawlMode::MangaPark;
    } else if ("y8" == modeString || "CrawlerMode::Y8" == modeString || "CrawlMode::Y8" == modeString) {
        mode = CrawlMode::Y8;
    } else if ("youtube" == modeString || "CrawlerMode::Youtube" == modeString || "CrawlMode::Youtube" == modeString) {
        mode = CrawlMode::Youtube;
    }
    return mode;
}

CrawlMode WebCrawler::convertWebLinkToCrawlerMode(string const& webLink) const {
    CrawlMode mode(CrawlMode::Empty);
    if (isStringFoundInsideTheOtherStringNotCaseSensitive(webLink, "chia-anime.tv")) {
        mode = CrawlMode::ChiaAnime;
    } else if (isStringFoundInsideTheOtherStringNotCaseSensitive(webLink, "doujin-moe.us")) {
        mode = CrawlMode::DoujinMoe;
    } else if (
        isStringFoundInsideTheOtherStringNotCaseSensitive(webLink, "g.e-h") &&
        isStringFoundInsideTheOtherStringNotCaseSensitive(webLink, ".org")) {
        mode = CrawlMode::Gehen;
    } else if (isStringFoundInsideTheOtherStringNotCaseSensitive(webLink, "guromanga.com")) {
        mode = CrawlMode::GuroManga;
    } else if (isStringFoundInsideTheOtherStringNotCaseSensitive(webLink, "hbrowse.com")) {
        mode = CrawlMode::HBrowse;
    } else if (
        isStringFoundInsideTheOtherStringNotCaseSensitive(webLink, "h") &&
        isStringFoundInsideTheOtherStringNotCaseSensitive(webLink, "2read.com")) {
        mode = CrawlMode::H2Read;
    } else if (isStringFoundInsideTheOtherStringNotCaseSensitive(webLink, "mangafox.me")) {
        mode = CrawlMode::Mangafox;
    } else if (isStringFoundInsideTheOtherStringNotCaseSensitive(webLink, "mangafox.me")) {
        mode = CrawlMode::MangafoxWithVolume;
    } else if (isStringFoundInsideTheOtherStringNotCaseSensitive(webLink, "mangahere.co")) {
        mode = CrawlMode::Mangahere;
    } else if (isStringFoundInsideTheOtherStringNotCaseSensitive(webLink, "mangapark.me")) {
        mode = CrawlMode::MangaPark;
    } else if (isStringFoundInsideTheOtherStringNotCaseSensitive(webLink, "y8.com")) {
        mode = CrawlMode::Y8;
    } else if (isStringFoundInsideTheOtherStringNotCaseSensitive(webLink, "youtube.com")) {
        mode = CrawlMode::Youtube;
    }
    return mode;
}

CrawlState WebCrawler::convertStringToCrawlerState(string const& stateString) const {
    CrawlState state(CrawlState::Empty);
    if ("CrawlState::Unknown" == stateString) {
        state = CrawlState::Unknown;
    } else if ("CrawlState::Active" == stateString) {
        state = CrawlState::Active;
    } else if ("CrawlState::CurrentDownloadIsFinished" == stateString) {
        state = CrawlState::CurrentDownloadIsFinished;
    } else if ("CrawlState::DownloadedFileIsInvalid" == stateString) {
        state = CrawlState::DownloadedFileIsInvalid;
    } else if ("CrawlState::DownloadedFileSizeIsLessThanExpected" == stateString) {
        state = CrawlState::DownloadedFileSizeIsLessThanExpected;
    } else if ("CrawlState::DownloadFailsAndRetryIsNeeded" == stateString) {
        state = CrawlState::DownloadFailsAndRetryIsNeeded;
    } else if ("CrawlState::LinksAreInvalid" == stateString) {
        state = CrawlState::LinksAreInvalid;
    } else if ("CrawlState::NextLinkIsInvalid" == stateString) {
        state = CrawlState::NextLinkIsInvalid;
    }
    return state;
}

#define GET_ENUM_STRING(en) \
    case en:                \
        return #en;

string WebCrawler::convertCrawlerModeToString(CrawlMode const mode) const {
    switch (mode) {
        GET_ENUM_STRING(CrawlMode::Empty)
        GET_ENUM_STRING(CrawlMode::Unknown)
        GET_ENUM_STRING(CrawlMode::ChiaAnime)
        GET_ENUM_STRING(CrawlMode::DoujinMoe)
        GET_ENUM_STRING(CrawlMode::Gehen)
        GET_ENUM_STRING(CrawlMode::GuroManga)
        GET_ENUM_STRING(CrawlMode::HBrowse)
        GET_ENUM_STRING(CrawlMode::H2Read)
        GET_ENUM_STRING(CrawlMode::Mangafox)
        GET_ENUM_STRING(CrawlMode::MangafoxWithVolume)
        GET_ENUM_STRING(CrawlMode::Mangahere)
        GET_ENUM_STRING(CrawlMode::MangaPark)
        GET_ENUM_STRING(CrawlMode::Y8)
        GET_ENUM_STRING(CrawlMode::Youtube)
    }
    return "";
}

string WebCrawler::convertCrawlerStateToString(CrawlState const state) const {
    switch (state) {
        GET_ENUM_STRING(CrawlState::Empty)
        GET_ENUM_STRING(CrawlState::Unknown)
        GET_ENUM_STRING(CrawlState::Active)
        GET_ENUM_STRING(CrawlState::CurrentDownloadIsFinished)
        GET_ENUM_STRING(CrawlState::DownloadedFileIsInvalid)
        GET_ENUM_STRING(CrawlState::DownloadedFileSizeIsLessThanExpected)
        GET_ENUM_STRING(CrawlState::DownloadFailsAndRetryIsNeeded)
        GET_ENUM_STRING(CrawlState::LinksAreInvalid)
        GET_ENUM_STRING(CrawlState::NextLinkIsInvalid)
    }
    return "";
}

#undef GET_ENUM_STRING

}  // namespace aprgWebCrawler
