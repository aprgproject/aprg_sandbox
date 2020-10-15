#pragma once

namespace aprgWebCrawler
{

enum class CrawlState{
    Empty,
    Unknown,
    Active,    DownloadedFileIsInvalid,
    LinksAreInvalid,
    NextLinkIsInvalid
};

}
