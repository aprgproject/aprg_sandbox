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

}
