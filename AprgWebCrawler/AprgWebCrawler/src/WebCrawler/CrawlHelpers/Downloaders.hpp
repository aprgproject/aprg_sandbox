#pragma once

#include <CrawlMode.hpp>
#include <PathHandlers/AlbaWebPathHandler.hpp>
#include <PathHandlers/AlbaWindowsPathHandler.hpp>

namespace aprgWebCrawler
{

namespace Downloaders
{
    bool downloadBinaryFile(alba::AlbaWebPathHandler const& fileToDownloadWebPathHandler, alba::AlbaWindowsPathHandler const& downloadPathHandler, CrawlMode mode);
    bool downloadFileAsText(alba::AlbaWebPathHandler const& fileToDownloadWebPathHandler, alba::AlbaWindowsPathHandler const& downloadPathHandler);
    void downloadFileUsingPhantomJs(alba::AlbaWebPathHandler const& fileToDownloadWebPathHandler, alba::AlbaWindowsPathHandler const& downloadPathHandler);
}

}
