#include "WebCrawler.hpp"

#include <CrawlConfiguration/CrawlConfiguration.hpp>
#include <CurlInterface.hpp>

using namespace alba;
using namespace curl::CurlInterface;

namespace aprgWebCrawler
{

bool WebCrawler::downloadBinaryFile(
        AlbaWebPathHandler const& fileToDownloadWebPathHandler,
        AlbaWindowsPathHandler const& downloadPathHandler) const
{
    bool isSuccessful(false);
    CrawlConfiguration configuration(m_mode);
    DownloadLowSpeedLimitConfigurationOptional downloadLowSpeedLimitConfigurationOptional(configuration.getDownloadLowSpeedLimitConfigurationOptional());
    if(downloadLowSpeedLimitConfigurationOptional)
    {
        curl::CurlInterface::lowSpeedLimit = downloadLowSpeedLimitConfigurationOptional.getReference().m_lowSpeedLimit;
        curl::CurlInterface::lowSpeedTime = downloadLowSpeedLimitConfigurationOptional.getReference().m_lowSpeedTime;
    }
    if(configuration.isFileToBeDownloadUntilSuccessful())
    {
        isSuccessful = downloadBinaryFileUntilSuccessful<ConfigType::LowSpeedLimitAndMozillaFireFoxAndPrintDownloadProgress>(fileToDownloadWebPathHandler, downloadPathHandler);
    }
    else
    {
        isSuccessful = downloadBinaryFileWithFiniteNumberOfTries<ConfigType::LowSpeedLimitAndMozillaFireFoxAndPrintDownloadProgress>(fileToDownloadWebPathHandler, downloadPathHandler, configuration.getNumberOfRetries());
    }
    return isSuccessful;
}

bool WebCrawler::downloadFileAsText(
        AlbaWebPathHandler const& fileToDownloadWebPathHandler,
        AlbaWindowsPathHandler const& downloadPathHandler) const
{
    return downloadUntilSuccessful<ConfigType::LowSpeedLimitAndMozillaFireFox>(fileToDownloadWebPathHandler, downloadPathHandler);
}

}
