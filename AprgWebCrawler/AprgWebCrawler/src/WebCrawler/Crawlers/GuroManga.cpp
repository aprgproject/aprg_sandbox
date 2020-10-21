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

void OneDownloadPerPageCrawler::retrieveLinksForGuroManga(AlbaWebPathHandler const& webLinkPathHandler)
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
    bool isDivClassImage(false);
    string title;
    AlbaFileReader htmlFileReader(htmlFileStream);
    while (htmlFileReader.isNotFinished())
    {
        string lineInHtmlFile(htmlFileReader.simpleGetLine());
        if(isStringFoundInsideTheOtherStringCaseSensitive(lineInHtmlFile, R"(<div class="page-image">)"))
        {
            isDivClassImage = true;
        }
        else if(isDivClassImage && isStringFoundInsideTheOtherStringCaseSensitive(lineInHtmlFile, R"(<a href=")"))
        {
            m_linkForNextHtml = getStringInBetweenTwoStrings(lineInHtmlFile, R"(<a href=")", R"(")");
        }
        else if(isDivClassImage && isStringFoundInsideTheOtherStringCaseSensitive(lineInHtmlFile, R"(<img src=")"))
        {
            m_linkForCurrentFileToDownload = getStringInBetweenTwoStrings(lineInHtmlFile, R"(<img src=")", R"(")");
            stringHelper::transformReplaceStringIfFound(m_linkForCurrentFileToDownload, R"(&#039;)", R"(')" ); // fix tis
            isDivClassImage = false;
            cout << m_linkForCurrentFileToDownload <<endl;
        }
        else if(isDivClassImage && isStringFoundInsideTheOtherStringCaseSensitive(lineInHtmlFile, R"(<title>)"))
        {
            title = getStringAndReplaceNonAlphanumericCharactersToUnderScore(
                        getStringInBetweenTwoStrings(lineInHtmlFile, R"(<title>)", R"(</title>)"));
        }

    }
    AlbaWebPathHandler imageWebPathHandler(webLinkPathHandler);
    imageWebPathHandler.gotoLink(m_linkForCurrentFileToDownload);
    m_localPathForCurrentFileToDownload =
            m_webCrawler.getDownloadDirectory()
            + title
            + R"(\)"
            + imageWebPathHandler.getFile();
}

}
