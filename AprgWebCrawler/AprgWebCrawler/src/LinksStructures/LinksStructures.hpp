#pragma once

#include <string>

namespace alba
{

struct LinksForHtmlAndFileToDownload
{
    std::string linkForNextHtml;
    std::string linkForCurrentFileToDownload;
    std::string localPathForCurrentFileToDownload;
    bool isInvalid() const;
    void printLinks() const;
};

struct LinksForChiaAnime
{
    std::string linkForNextHtml;
    std::string linkForDownloadPage;
    std::string linkForCurrentVideo;
    std::string localPathForCurrentVideo;
    bool isInvalid() const;
    void printLinks() const;
};

struct LinksForYoutube
{
    std::string linkForVideo;
    std::string localPathForCurrentVideo;
    bool isInvalid() const;
    void printLinks() const;
};

}
