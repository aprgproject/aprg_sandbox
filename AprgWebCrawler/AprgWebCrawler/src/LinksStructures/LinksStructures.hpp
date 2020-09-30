#pragma once

#include <string>

using std::string;

namespace alba
{

struct LinksForHtmlAndFileToDownload
{
    string linkForNextHtml;
    string linkForCurrentFileToDownload;
    string localPathForCurrentFileToDownload;
    bool isInvalid() const;
    void printLinks() const;
};

struct LinksForChiaAnime
{
    string linkForNextHtml;
    string linkForDownloadPage;
    string linkForCurrentVideo;
    string localPathForCurrentVideo;
    bool isInvalid() const;
    void printLinks() const;
};

struct LinksForYoutube
{
    string linkForVideo;
    string localPathForCurrentVideo;
    bool isInvalid() const;
    void printLinks() const;
};

}
