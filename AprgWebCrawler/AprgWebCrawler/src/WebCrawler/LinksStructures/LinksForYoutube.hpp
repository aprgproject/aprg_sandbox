#pragma once

#include <string>

namespace aprgWebCrawler
{

struct LinksForYoutube
{
    std::string linkForVideo;
    std::string localPathForCurrentVideo;
    bool isInvalid() const;
    void printLinks() const;
};

}
