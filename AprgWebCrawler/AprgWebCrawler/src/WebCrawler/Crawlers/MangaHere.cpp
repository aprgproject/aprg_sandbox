#include <Common/File/AlbaFileReader.hpp>
#include <Common/String/AlbaStringHelper.hpp>
#include <WebCrawler/CrawlHelpers/Downloaders.hpp>
#include <WebCrawler/Crawlers/OneDownloadPerPageCrawler.hpp>

#include <fstream>
#include <iostream>

using namespace alba;
using namespace alba::stringHelper;
using namespace aprgWebCrawler::Downloaders;
using namespace std;

namespace aprgWebCrawler {

void OneDownloadPerPageCrawler::retrieveLinksForMangaHere(AlbaWebPathHandler const& webLinkPathHandler) {
    AlbaLocalPathHandler downloadPathHandler(m_webCrawler.getDownloadDirectory() + R"(\temp.html)");
    downloadFileWithDefaultSettings(webLinkPathHandler, downloadPathHandler);
    ifstream htmlFileStream(downloadPathHandler.getFullPath());
    if (!htmlFileStream.is_open()) {
        cout << "Cannot open html file.\n";
        cout << "File to read:" << downloadPathHandler.getFullPath() << "\n";
    } else {
        bool insideImportantSection(false);
        string nextPageLink;
        string nextChapterLink;
        AlbaFileReader htmlFileReader(htmlFileStream);
        while (htmlFileReader.isNotFinished()) {
            string lineInHtmlFile(htmlFileReader.getLine());
            if (isStringFoundInsideTheOtherStringCaseSensitive(lineInHtmlFile, R"(section class="read_img")")) {
                insideImportantSection = true;
            } else if (
                insideImportantSection &&
                isStringFoundInsideTheOtherStringCaseSensitive(lineInHtmlFile, R"(onclick="return next_page();")")) {
                nextPageLink = getStringInBetweenTwoStrings(lineInHtmlFile, R"(<a href=")", R"(")");
            } else if (
                insideImportantSection &&
                isStringFoundInsideTheOtherStringCaseSensitive(lineInHtmlFile, R"(img src=")")) {
                m_linkForCurrentFileToDownload = getStringInBetweenTwoStrings(lineInHtmlFile, R"(img src=")", R"(")");
            } else if (isStringFoundInsideTheOtherStringCaseSensitive(
                           lineInHtmlFile, "<strong>Next Chapter:</strong>")) {
                nextChapterLink = getStringInBetweenTwoStrings(lineInHtmlFile, R"(<a href=")", R"(")");
            } else if (
                insideImportantSection &&
                isStringFoundInsideTheOtherStringCaseSensitive(lineInHtmlFile, "</section>")) {
                insideImportantSection = false;
            } else if (isStringFoundInsideTheOtherStringCaseSensitive(
                           lineInHtmlFile, R"(<div class="mangaread_error">)")) {
                cout << "Final Chapter found\n";
                return;
            }
        }
        if ("javascript:void(0);" == nextPageLink) {
            cout << "New chapter. NextChapterLink :" << nextChapterLink << "\n";
            m_linkForNextHtml = nextChapterLink;
        } else {
            m_linkForNextHtml = nextPageLink;
        }
        AlbaWebPathHandler imageWebPathHandler(webLinkPathHandler);
        imageWebPathHandler.gotoLink(m_linkForCurrentFileToDownload);
        m_localPathForCurrentFileToDownload = m_webCrawler.getDownloadDirectory() +
                                              webLinkPathHandler.getImmediateDirectoryName() + R"(\)" +
                                              imageWebPathHandler.getFile();
    }
}

}  // namespace aprgWebCrawler
