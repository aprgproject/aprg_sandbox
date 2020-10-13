#pragma once

#include <string>

namespace alba
{

struct LinksForYoutube
{
    std::string linkForVideo;
    std::string localPathForCurrentVideo;
    bool isInvalid() const;
    void printLinks() const;
};

}
