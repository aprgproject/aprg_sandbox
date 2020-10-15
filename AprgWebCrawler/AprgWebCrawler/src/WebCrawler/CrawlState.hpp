#pragma once

namespace aprgWebCrawler
{

enum class CrawlState
{
    Empty,
    Unknown,
    Active,
    DownloadedFileIsInvalid,
    DownloadedFileSizeIsLessThanExpected,
    LinksAreInvalid,
    NextLinkIsInvalid
};

}
