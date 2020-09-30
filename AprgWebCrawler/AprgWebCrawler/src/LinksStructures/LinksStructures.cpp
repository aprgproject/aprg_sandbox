#include "LinksStructures.hpp"

#include <iostream>

using namespace std;

namespace alba
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

bool LinksForChiaAnime::isInvalid() const
{
    return linkForDownloadPage.empty() || linkForCurrentVideo.empty() || localPathForCurrentVideo.empty();
}

void LinksForChiaAnime::printLinks() const
{
    cout << "LinkForNextHtml : " << linkForNextHtml << endl;
    cout << "LinkForDownloadPage : " << linkForDownloadPage << endl;
    cout << "LinkForCurrentVideo : " << linkForCurrentVideo << endl;
    cout << "LocalPathForCurrentVideo : " << localPathForCurrentVideo << endl;
}

bool LinksForYoutube::isInvalid() const
{
    return linkForVideo.empty() || localPathForCurrentVideo.empty();
}

void LinksForYoutube::printLinks() const
{
    cout << "linkForVideo : " << linkForVideo << endl;
    cout << "videoFileName : " << localPathForCurrentVideo << endl;
}

}
