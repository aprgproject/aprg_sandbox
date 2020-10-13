#pragma once

namespace alba
{

enum class CrawlState
{
    Empty,
    Active,
    DownloadedFileIsInvalid,
    LinksAreInvalid,
    NextLinkIsInvalid
};

}
