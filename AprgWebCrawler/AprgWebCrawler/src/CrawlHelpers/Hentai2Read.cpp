#include "WebCrawler.hpp"

#include <AlbaFileReader.hpp>
#include <AlbaStringHelper.hpp>#include <fstream>
#include <iostream>

using namespace std;
using alba::stringHelper::getStringInBetweenTwoStrings;
using alba::stringHelper::isStringFoundInsideTheOtherStringCaseSensitive;

namespace alba
{

LinksForHtmlAndFileToDownload WebCrawler::getLinksForHentai2Read(AlbaWebPathHandler const& webLinkPathHandler, string const& pathOfHtmlFile) const
{
    LinksForHtmlAndFileToDownload links;
    ifstream htmlFileStream(pathOfHtmlFile);    if(!htmlFileStream.is_open())
    {
        cout << "Cannot open html file." << endl;
        cout << "File to read:" << pathOfHtmlFile << endl;        return links;
    }
    AlbaFileReader htmlFileReader(htmlFileStream);
    while (htmlFileReader.isNotFinished())
    {
        string lineInHtmlFile(htmlFileReader.simpleGetLine());
        if(isStringFoundInsideTheOtherStringCaseSensitive(lineInHtmlFile, R"(<img id="img_mng_enl")"))
        {
            links.linkForCurrentFileToDownload = getStringInBetweenTwoStrings(lineInHtmlFile, R"( src=")", R"(")");
        }
        else if(isStringFoundInsideTheOtherStringCaseSensitive(lineInHtmlFile, R"(Next</a><br/>)"))
        {
            links.linkForNextHtml = getStringInBetweenTwoStrings(lineInHtmlFile, R"(<a href=")", R"(")");
        }
    }
    AlbaWebPathHandler imageWebPathHandler(webLinkPathHandler);
    imageWebPathHandler.gotoLink(links.linkForCurrentFileToDownload);
    AlbaWebPathHandler chapterWebPathHandler(webLinkPathHandler);
    chapterWebPathHandler.goUp();
    links.localPathForCurrentFileToDownload = m_workingPathHandler.getDirectory() + R"(chapter)" + chapterWebPathHandler.getImmediateDirectoryName() + R"(\)" + imageWebPathHandler.getFile();
    return links;
}

}
