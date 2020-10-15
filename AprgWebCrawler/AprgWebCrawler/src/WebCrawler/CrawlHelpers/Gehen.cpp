#include "WebCrawler.hpp"

#include <AlbaFileReader.hpp>
#include <AlbaStringHelper.hpp>
#include <fstream>
#include <iostream>

using namespace alba;
using namespace alba::stringHelper;
using namespace std;

namespace aprgWebCrawler
{

LinksForHtmlAndFileToDownload WebCrawler::getLinksForGehen(AlbaWebPathHandler const& webLinkPathHandler, string const& pathOfHtmlFile) const
{
    LinksForHtmlAndFileToDownload links;
    ifstream htmlFileStream(pathOfHtmlFile);
    if(!htmlFileStream.is_open())
    {
        cout << "Cannot open html file." << endl;
        cout << "File to read:" << pathOfHtmlFile << endl;
        return links;
    }
    AlbaFileReader htmlFileReader(htmlFileStream);
    while (htmlFileReader.isNotFinished())
    {
        string lineInHtmlFile(htmlFileReader.simpleGetLine());
        if(isStringFoundInsideTheOtherStringCaseSensitive(lineInHtmlFile, R"(<img id="img" src=")"))
        {
            links.linkForCurrentFileToDownload = getStringInBetweenTwoStrings(lineInHtmlFile, R"(<img id="img" src=")", R"(")");
            int indexOfPreviousPng = lineInHtmlFile.find("http://ehgt.org/g/p.png");
            if(stringHelper::isNotNpos(indexOfPreviousPng))
            {
                links.linkForNextHtml = getStringInBetweenTwoStrings(lineInHtmlFile, R"(href=")", R"(")", indexOfPreviousPng);
            }
        }
    }
    AlbaWebPathHandler imageWebPathHandler(webLinkPathHandler);
    imageWebPathHandler.gotoLink(links.linkForCurrentFileToDownload);
    links.localPathForCurrentFileToDownload = m_downloadDirectoryPathHandler.getDirectory() + R"(\images\)" + imageWebPathHandler.getFile();
    return links;
}

}
