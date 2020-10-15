#include "WebCrawler.hpp"

#include <AlbaFileReader.hpp>
#include <AlbaStringHelper.hpp>
#include <fstream>
#include <iostream>

using namespace std;

using alba::stringHelper::getStringInBetweenTwoStrings;
using alba::stringHelper::isStringFoundInsideTheOtherStringCaseSensitive;

namespace alba
{

LinksForHtmlAndFileToDownload WebCrawler::getLinksForMangaFox(AlbaWebPathHandler const& webLinkPathHandler, string const& pathOfHtmlFile) const
{
    LinksForHtmlAndFileToDownload links = getNextLinkAndImageLinkForMangaFox(pathOfHtmlFile);
    AlbaWebPathHandler imageWebPathHandler(webLinkPathHandler);
    imageWebPathHandler.gotoLink(links.linkForCurrentFileToDownload);
    links.localPathForCurrentFileToDownload = m_workingPathHandler.getDirectory() + webLinkPathHandler.getImmediateDirectoryName() + R"(\)" + imageWebPathHandler.getFile();
    return links;
}

LinksForHtmlAndFileToDownload WebCrawler::getLinksForMangaFoxSaveInVolumeAndChapter(AlbaWebPathHandler const& webLinkPathHandler, string const& pathOfHtmlFile) const
{
    AlbaWebPathHandler webPathForFolderName(webLinkPathHandler);
    LinksForHtmlAndFileToDownload links = getNextLinkAndImageLinkForMangaFox(pathOfHtmlFile);
    string folderName(webPathForFolderName.getImmediateDirectoryName());
    webPathForFolderName.goUp();
    folderName = webPathForFolderName.getImmediateDirectoryName() + "_" + folderName;
    AlbaWebPathHandler imageWebPathHandler(webLinkPathHandler);
    imageWebPathHandler.gotoLink(links.linkForCurrentFileToDownload);
    links.localPathForCurrentFileToDownload = m_workingPathHandler.getDirectory() + folderName + R"(\)" + imageWebPathHandler.getFile();
    return links;
}

LinksForHtmlAndFileToDownload WebCrawler::getNextLinkAndImageLinkForMangaFox(string const& pathOfHtmlFile) const
{
    LinksForHtmlAndFileToDownload links;
    ifstream htmlFileStream(pathOfHtmlFile);
    if(!htmlFileStream.is_open())
    {
        cout << "Cannot open html file." << endl;
        cout << "File to read:" << pathOfHtmlFile << endl;
        return links;
    }
    string nextPageLink;
    string nextChapterLink;
    string onClickNextPage;
    AlbaFileReader htmlFileReader(htmlFileStream);
    while (htmlFileReader.isNotFinished())
    {
        string lineInHtmlFile(htmlFileReader.simpleGetLine());
        if(isStringFoundInsideTheOtherStringCaseSensitive(lineInHtmlFile, R"***(onclick="return enlarge()">)***"))
        {
            string nextLineInHtmlFile(htmlFileReader.simpleGetLine());
            if(isStringFoundInsideTheOtherStringCaseSensitive(nextLineInHtmlFile, R"(<img src=")"))
            {
                links.linkForCurrentFileToDownload = getStringInBetweenTwoStrings(nextLineInHtmlFile, R"(img src=")", R"(")");
            }
        }
        else if(isStringFoundInsideTheOtherStringCaseSensitive(lineInHtmlFile, R"(class="btn next_page"><span></span>next page</a>)"))
        {
            nextPageLink = getStringInBetweenTwoStrings(lineInHtmlFile, R"(<a href=")", R"(")");
            onClickNextPage = getStringInBetweenTwoStrings(lineInHtmlFile, R"(onclick=")", R"(")");
        }
        else if(isStringFoundInsideTheOtherStringCaseSensitive(lineInHtmlFile, R"(<p><span>Next Chapter:</span> <a href=")"))
        {
            nextChapterLink = getStringInBetweenTwoStrings(lineInHtmlFile, R"(<a href=")", R"(")");
        }
    }
    if("next_chapter()" == onClickNextPage || "javascript:void(0);" == nextPageLink)
    {
        cout << "New chapter. NextChapterLink :" << nextChapterLink << endl;
        links.linkForNextHtml = nextChapterLink;
    }
    else
    {
        links.linkForNextHtml = nextPageLink;
    }
    return links;
}

}
