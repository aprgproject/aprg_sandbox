#include <CrawlHelpers/Downloaders.hpp>
#include <Crawlers/OneDownloadPerPageCrawler.hpp>
#include <File/AlbaFileReader.hpp>
#include <String/AlbaStringHelper.hpp>

#include <fstream>
#include <iostream>

using namespace alba;
using namespace alba::stringHelper;
using namespace aprgWebCrawler::Downloaders;
using namespace std;

namespace aprgWebCrawler
{

void OneDownloadPerPageCrawler::retrieveLinksForH2Read(AlbaWebPathHandler const& webLinkPathHandler)
{
    AlbaLocalPathHandler downloadPathHandler(m_webCrawler.getDownloadDirectory() + R"(\temp.html)");
    downloadFileAsText(webLinkPathHandler, downloadPathHandler);
    ifstream htmlFileStream(downloadPathHandler.getFullPath());
    if(!htmlFileStream.is_open())
    {
        cout << "Cannot open html file." << endl;
        cout << "File to read:" << downloadPathHandler.getFullPath() << endl;
    }
    else
    {
        AlbaFileReader htmlFileReader(htmlFileStream);
        while (htmlFileReader.isNotFinished())
        {
            string lineInHtmlFile(htmlFileReader.getLine());
            if(isStringFoundInsideTheOtherStringCaseSensitive(lineInHtmlFile, R"(<img id="img_mng_enl")"))
            {
                m_linkForCurrentFileToDownload = getStringInBetweenTwoStrings(lineInHtmlFile, R"( src=")", R"(")");
            }
            else if(isStringFoundInsideTheOtherStringCaseSensitive(lineInHtmlFile, R"(Next</a><br/>)"))
            {
                m_linkForNextHtml = getStringInBetweenTwoStrings(lineInHtmlFile, R"(<a href=")", R"(")");
            }
        }
        AlbaWebPathHandler imageWebPathHandler(webLinkPathHandler);
        imageWebPathHandler.gotoLink(m_linkForCurrentFileToDownload);
        AlbaWebPathHandler chapterWebPathHandler(webLinkPathHandler);
        chapterWebPathHandler.goUp();
        m_localPathForCurrentFileToDownload = m_webCrawler.getDownloadDirectory() + R"(chapter)" + chapterWebPathHandler.getImmediateDirectoryName() + R"(\)" + imageWebPathHandler.getFile();
    }
}

}
