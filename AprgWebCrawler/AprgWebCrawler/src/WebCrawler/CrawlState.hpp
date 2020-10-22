#pragma once

namespace aprgWebCrawler
{

enum class CrawlState
{
    Empty,
    Unknown,
    Active,
    CurrentDownloadIsFinished,
    DownloadedFileIsInvalid,
    DownloadedFileSizeIsLessThanExpected,
    DownloadFailsRepetitively,
    LinksAreInvalid,
    NextLinkIsInvalid
};

}
