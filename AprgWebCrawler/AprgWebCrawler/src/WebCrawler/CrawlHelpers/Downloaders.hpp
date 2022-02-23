#pragma once

#include <Common/PathHandler/AlbaLocalPathHandler.hpp>
#include <Common/PathHandler/AlbaWebPathHandler.hpp>
#include <WebCrawler/CrawlMode.hpp>

namespace aprgWebCrawler{

namespace Downloaders
{    bool downloadBinaryFile(alba::AlbaWebPathHandler const& fileToDownloadWebPathHandler, alba::AlbaLocalPathHandler const& downloadPathHandler, CrawlMode mode);
    bool downloadFileWithDefaultSettings(alba::AlbaWebPathHandler const& fileToDownloadWebPathHandler, alba::AlbaLocalPathHandler const& downloadPathHandler);
}

}
