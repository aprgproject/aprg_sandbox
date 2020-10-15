#include "LinksForChiaAnime.hpp"

#include <iostream>

using namespace std;

namespace aprgWebCrawler
{

bool LinksForChiaAnime::isInvalid() const{
    return linkForDownloadPage.empty() || linkForCurrentVideo.empty() || localPathForCurrentVideo.empty();
}
void LinksForChiaAnime::printLinks() const
{
    cout << "LinkForNextHtml : " << linkForNextHtml << endl;
    cout << "LinkForDownloadPage : " << linkForDownloadPage << endl;
    cout << "LinkForCurrentVideo : " << linkForCurrentVideo << endl;
    cout << "LocalPathForCurrentVideo : " << localPathForCurrentVideo << endl;
}

}
