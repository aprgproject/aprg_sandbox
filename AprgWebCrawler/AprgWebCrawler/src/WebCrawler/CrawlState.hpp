#pragma once

namespace alba
{

enum class CrawlState
{
    Empty,
    Unknown,
    Active,
    DownloadedFileIsInvalid,
    LinksAreInvalid,
    NextLinkIsInvalid
};

}
