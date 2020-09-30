#include "AprgWebCrawler.hpp"

#include <AlbaFileReader.hpp>
#include <AlbaStringHelper.hpp>
#include <fstream>
#include <iostream>

using namespace std;

using alba::stringHelper::getStringAndReplaceNonAlphanumericCharactersToUnderScore;
using alba::stringHelper::getStringInBetweenTwoStrings;
using alba::stringHelper::isStringFoundInsideTheOtherStringCaseSensitive;

namespace alba
{

LinksForHtmlAndFileToDownload AprgWebCrawler::getLinksForGuroManga(AlbaWebPathHandler const& webLinkPathHandler, string const& pathOfHtmlFile) const
{
    LinksForHtmlAndFileToDownload links;
    ifstream htmlFileStream(pathOfHtmlFile);
    if(!htmlFileStream.is_open())
    {
        cout << "Cannot open html file." << endl;
        cout << "File to read:" << pathOfHtmlFile << endl;
        return links;
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
            links.linkForNextHtml = getStringInBetweenTwoStrings(lineInHtmlFile, R"(<a href=")", R"(")");
        }
        else if(isDivClassImage && isStringFoundInsideTheOtherStringCaseSensitive(lineInHtmlFile, R"(<img src=")"))
        {
            links.linkForCurrentFileToDownload = getStringInBetweenTwoStrings(lineInHtmlFile, R"(<img src=")", R"(")");
            stringHelper::transformReplaceStringIfFound(links.linkForCurrentFileToDownload, R"(&#039;)", R"(')" ); // fix tis
            isDivClassImage = false;
            cout << links.linkForCurrentFileToDownload <<endl;
        }
        else if(isDivClassImage && isStringFoundInsideTheOtherStringCaseSensitive(lineInHtmlFile, R"(<title>)"))
        {
            title = getStringAndReplaceNonAlphanumericCharactersToUnderScore(
                        getStringInBetweenTwoStrings(lineInHtmlFile, R"(<title>)", R"(</title>)"));
        }

    }
    AlbaWebPathHandler imageWebPathHandler(webLinkPathHandler);
    imageWebPathHandler.gotoLink(links.linkForCurrentFileToDownload);
    links.localPathForCurrentFileToDownload =
            m_workingPathHandler.getDirectory()
            + title
            + R"(\)"
            + imageWebPathHandler.getFile();
    links.printLinks();
    return links;
}

}
