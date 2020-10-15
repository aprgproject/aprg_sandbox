#pragma once

#include <string>

namespace aprgWebCrawler
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
