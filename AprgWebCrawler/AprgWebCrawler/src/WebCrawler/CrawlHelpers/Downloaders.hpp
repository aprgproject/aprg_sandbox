#pragma once

#include <CrawlMode.hpp>
#include <PathHandlers/AlbaLocalPathHandler.hpp>
#include <PathHandlers/AlbaWebPathHandler.hpp>

namespace aprgWebCrawler
{

namespace Downloaders
{
    bool downloadBinaryFile(alba::AlbaWebPathHandler const& fileToDownloadWebPathHandler, alba::AlbaLocalPathHandler const& downloadPathHandler, CrawlMode mode);
    bool downloadFileAsText(alba::AlbaWebPathHandler const& fileToDownloadWebPathHandler, alba::AlbaLocalPathHandler const& downloadPathHandler);
    void downloadFileUsingPhantomJs(alba::AlbaWebPathHandler const& fileToDownloadWebPathHandler, alba::AlbaLocalPathHandler const& downloadPathHandler);
}

}
