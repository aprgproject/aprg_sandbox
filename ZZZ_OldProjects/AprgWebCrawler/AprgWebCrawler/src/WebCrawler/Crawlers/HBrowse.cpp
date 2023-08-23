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

void OneDownloadPerPageCrawler::retrieveLinksForHBrowse(AlbaWebPathHandler const& webLinkPathHandler) {
    AlbaLocalPathHandler downloadPathHandler(m_webCrawler.getDownloadDirectory() + R"(\temp.html)");
    downloadFileWithDefaultSettings(webLinkPathHandler, downloadPathHandler);
    ifstream htmlFileStream(downloadPathHandler.getFullPath());
    if (!htmlFileStream.is_open()) {
        cout << "Cannot open html file.\n";
        cout << "File to read:" << downloadPathHandler.getFullPath() << "\n";
    } else {
        AlbaFileReader htmlFileReader(htmlFileStream);
        while (htmlFileReader.isNotFinished()) {
            string lineInHtmlFile(htmlFileReader.getLine());
            if (isStringFoundInsideTheOtherStringCaseSensitive(lineInHtmlFile, R"(<img id="mangaImage")")) {
                m_linkForCurrentFileToDownload = getStringInBetweenTwoStrings(lineInHtmlFile, R"( src=")", R"(")");
            }
            if (isStringFoundInsideTheOtherStringCaseSensitive(lineInHtmlFile, R"(<a name="next")")) {
                m_linkForNextHtml = getStringInBetweenTwoStrings(lineInHtmlFile, R"( href=")", R"(")");
            }
        }
        AlbaWebPathHandler imageWebPathHandler(webLinkPathHandler);
        imageWebPathHandler.gotoLink(m_linkForCurrentFileToDownload);
        m_localPathForCurrentFileToDownload = m_webCrawler.getDownloadDirectory() +
                                              imageWebPathHandler.getImmediateDirectoryName() + R"(\)" +
                                              imageWebPathHandler.getFile();
    }
}

}  // namespace aprgWebCrawler
