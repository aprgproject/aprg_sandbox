#include <Crawlers/OneDownloadPerPageCrawler.hpp>

#include <AlbaFileReader.hpp>
#include <AlbaStringHelper.hpp>
#include <fstream>
#include <iostream>

using namespace alba;
using namespace alba::stringHelper;
using namespace std;

namespace aprgWebCrawler
{

void OneDownloadPerPageCrawler::retrieveLinksForHBrowse(AlbaWebPathHandler const& webLinkPathHandler)
{
    AlbaWindowsPathHandler downloadPathHandler(m_webCrawler.getDownloadDirectory() + R"(\temp.html)");
    m_webCrawler.downloadFileAsText(webLinkPathHandler, downloadPathHandler);
    ifstream htmlFileStream(downloadPathHandler.getFullPath());
    if(!htmlFileStream.is_open())
    {
        cout << "Cannot open html file." << endl;
        cout << "File to read:" << downloadPathHandler.getFullPath() << endl;
        return;
    }
    AlbaFileReader htmlFileReader(htmlFileStream);
    while (htmlFileReader.isNotFinished())
    {
        string lineInHtmlFile(htmlFileReader.simpleGetLine());
        if(isStringFoundInsideTheOtherStringCaseSensitive(lineInHtmlFile, R"(<img id="mangaImage")"))
        {
            m_linkForCurrentFileToDownload = getStringInBetweenTwoStrings(lineInHtmlFile, R"( src=")", R"(")");
        }
        if(isStringFoundInsideTheOtherStringCaseSensitive(lineInHtmlFile, R"(<a name="next")"))
        {
            m_linkForNextHtml = getStringInBetweenTwoStrings(lineInHtmlFile, R"( href=")", R"(")");
        }
    }
    AlbaWebPathHandler imageWebPathHandler(webLinkPathHandler);
    imageWebPathHandler.gotoLink(m_linkForCurrentFileToDownload);
    m_localPathForCurrentFileToDownload = m_webCrawler.getDownloadDirectory() + imageWebPathHandler.getImmediateDirectoryName() + R"(\)" + imageWebPathHandler.getFile();
}

}
