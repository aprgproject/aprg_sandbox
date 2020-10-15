#include "WebCrawler.hpp"

#include <AlbaFileReader.hpp>
#include <AlbaStringHelper.hpp>
#include <fstream>
#include <iostream>

using namespace alba;
using namespace std;

using alba::stringHelper::getStringInBetweenTwoStrings;
using alba::stringHelper::isStringFoundInsideTheOtherStringCaseSensitive;

namespace aprgWebCrawler
{

LinksForHtmlAndFileToDownload WebCrawler::getLinksForY8(AlbaWebPathHandler const& webLinkPathHandler, string const& pathOfHtmlFile) const{
    LinksForHtmlAndFileToDownload links;
    ifstream htmlFileStream(pathOfHtmlFile);
    if(!htmlFileStream.is_open())    {
        cout << "Cannot open html file." << endl;
        cout << "File to read:" << pathOfHtmlFile << endl;
        return links;
    }
    AlbaFileReader htmlFileReader(htmlFileStream);
    while (htmlFileReader.isNotFinished())
    {
        string lineInHtmlFile(htmlFileReader.simpleGetLine());
        if(isStringFoundInsideTheOtherStringCaseSensitive(lineInHtmlFile, R"(<a class="controls-button maximize-button-no-js" href=")"))
        {
            links.linkForCurrentFileToDownload = getStringInBetweenTwoStrings(lineInHtmlFile, R"(<a class="controls-button maximize-button-no-js" href=")", R"(")");
        }
    }
    AlbaWebPathHandler flashWebPathHandler(webLinkPathHandler);
    flashWebPathHandler.gotoLink(links.linkForCurrentFileToDownload);
    links.localPathForCurrentFileToDownload = m_workingPathHandler.getDirectory() + R"(\Games\)" + flashWebPathHandler.getFile();
    links.linkForNextHtml = webLinkPathHandler.getFullPath();
    return links;
}


}
