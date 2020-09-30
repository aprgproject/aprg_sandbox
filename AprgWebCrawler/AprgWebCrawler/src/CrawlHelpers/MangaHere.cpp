#include "AprgWebCrawler.hpp"

#include <AlbaFileReader.hpp>
#include <AlbaStringHelper.hpp>
#include <fstream>
#include <iostream>

using namespace std;

using alba::stringHelper::getStringInBetweenTwoStrings;
using alba::stringHelper::isStringFoundInsideTheOtherStringCaseSensitive;

namespace alba
{

LinksForHtmlAndFileToDownload AprgWebCrawler::getLinksForMangaHere(AlbaWebPathHandler const& webLinkPathHandler, string const& pathOfHtmlFile) const
{
    LinksForHtmlAndFileToDownload links;
    ifstream htmlFileStream(pathOfHtmlFile);
    if(!htmlFileStream.is_open())
    {
        cout << "Cannot open html file." << endl;
        cout << "File to read:" << pathOfHtmlFile << endl;
        return links;
    }
    bool insideImportantSection(false);
    string nextPageLink;
    string nextChapterLink;
    AlbaFileReader htmlFileReader(htmlFileStream);
    while (htmlFileReader.isNotFinished())
    {
        string lineInHtmlFile(htmlFileReader.simpleGetLine());
        if(isStringFoundInsideTheOtherStringCaseSensitive(lineInHtmlFile, R"(section class="read_img")"))
        {
            insideImportantSection = true;
        }
        else if(insideImportantSection && isStringFoundInsideTheOtherStringCaseSensitive(lineInHtmlFile, R"(onclick="return next_page();")"))
        {
            nextPageLink = getStringInBetweenTwoStrings(lineInHtmlFile, R"(<a href=")", R"(")");
        }
        else if(insideImportantSection && isStringFoundInsideTheOtherStringCaseSensitive(lineInHtmlFile, R"(img src=")"))
        {
            links.linkForCurrentFileToDownload = getStringInBetweenTwoStrings(lineInHtmlFile, R"(img src=")", R"(")");
        }
        else if(isStringFoundInsideTheOtherStringCaseSensitive(lineInHtmlFile, "<strong>Next Chapter:</strong>"))
        {
            nextChapterLink = getStringInBetweenTwoStrings(lineInHtmlFile, R"(<a href=")", R"(")");
        }
        else if(insideImportantSection && isStringFoundInsideTheOtherStringCaseSensitive(lineInHtmlFile, "</section>"))
        {
            insideImportantSection = false;
        }
        else if(isStringFoundInsideTheOtherStringCaseSensitive(lineInHtmlFile, R"(<div class="mangaread_error">)"))
        {
            cout << "Final Chapter found" << endl;
            return links;
        }
    }
    if("javascript:void(0);" == nextPageLink)
    {
        cout << "New chapter. NextChapterLink :" << nextChapterLink << endl;
        links.linkForNextHtml = nextChapterLink;
    }
    else
    {
        links.linkForNextHtml = nextPageLink;
    }
    AlbaWebPathHandler imageWebPathHandler(webLinkPathHandler);
    imageWebPathHandler.gotoLink(links.linkForCurrentFileToDownload);
    links.localPathForCurrentFileToDownload = m_workingPathHandler.getDirectory() + webLinkPathHandler.getImmediateDirectoryName() + R"(\)" + imageWebPathHandler.getFile();
    return links;
}

}
