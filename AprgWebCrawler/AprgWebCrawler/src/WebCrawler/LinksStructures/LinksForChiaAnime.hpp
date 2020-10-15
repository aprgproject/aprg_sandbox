#pragma once

#include <string>

namespace aprgWebCrawler
{

struct LinksForChiaAnime{
    std::string linkForNextHtml;
    std::string linkForDownloadPage;
    std::string linkForCurrentVideo;    std::string localPathForCurrentVideo;
    bool isInvalid() const;
    void printLinks() const;
};

}
