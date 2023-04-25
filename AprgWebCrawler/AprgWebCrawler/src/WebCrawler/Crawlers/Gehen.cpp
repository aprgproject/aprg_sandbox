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

void OneDownloadPerPageCrawler::retrieveLinksForGehen(AlbaWebPathHandler const& webLinkPathHandler) {
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
            if (isStringFoundInsideTheOtherStringCaseSensitive(lineInHtmlFile, R"(<img id="img" src=")")) {
                m_linkForCurrentFileToDownload =
                    getStringInBetweenTwoStrings(lineInHtmlFile, R"(<img id="img" src=")", R"(")");
                int indexOfPreviousPng = lineInHtmlFile.find("http://ehgt.org/g/p.png");
                if (stringHelper::isNotNpos(indexOfPreviousPng)) {
                    m_linkForNextHtml =
                        getStringInBetweenTwoStrings(lineInHtmlFile, R"(href=")", R"(")", indexOfPreviousPng);
                }
            }
        }
        AlbaWebPathHandler imageWebPathHandler(webLinkPathHandler);
        imageWebPathHandler.gotoLink(m_linkForCurrentFileToDownload);
        m_localPathForCurrentFileToDownload =
            m_webCrawler.getDownloadDirectory() + R"(\images\)" + imageWebPathHandler.getFile();
    }
}

}  // namespace aprgWebCrawler
