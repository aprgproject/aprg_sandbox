#include "LinksForHtmlAndFileToDownload.hpp"

#include <iostream>

using namespace std;

namespace aprgWebCrawler
{

bool LinksForHtmlAndFileToDownload::isInvalid() const
{
    return linkForCurrentFileToDownload.empty() || localPathForCurrentFileToDownload.empty();
}

void LinksForHtmlAndFileToDownload::printLinks() const
{
    cout << "LinkForNextHtml : " << linkForNextHtml << endl;
    cout << "LinkForCurrentFileToDownload : " << linkForCurrentFileToDownload << endl;
    cout << "LocalPathForCurrentFileToDownload : " << localPathForCurrentFileToDownload << endl;
}

}
