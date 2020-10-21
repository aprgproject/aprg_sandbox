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
    Finished,
    LinksAreInvalid,
    NextLinkIsInvalid
};

}
