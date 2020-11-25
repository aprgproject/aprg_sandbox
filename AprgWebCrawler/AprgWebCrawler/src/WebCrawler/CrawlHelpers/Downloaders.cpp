#include "Downloaders.hpp"

#include <CrawlConfiguration/CrawlConfiguration.hpp>
#include <CurlInterface.hpp>

#include <windows.h>

#include <iostream>
#include <string>

#define PHANTOM_BIN_PATH APRG_DIR R"(PhantomJs\PhantomJs\bin\)"

using namespace alba;
using namespace curl::CurlInterface;
using namespace std;

namespace aprgWebCrawler
{

bool Downloaders::downloadBinaryFile(
        AlbaWebPathHandler const& fileToDownloadWebPathHandler,
        AlbaLocalPathHandler const& downloadPathHandler,
        CrawlMode mode)
{
    bool isSuccessful(false);
    CrawlConfiguration configuration(mode);
    DownloadLowSpeedLimitConfigurationOptional downloadLowSpeedLimitConfigurationOptional(configuration.getDownloadLowSpeedLimitConfigurationOptional());
    if(downloadLowSpeedLimitConfigurationOptional)
    {
        curl::CurlInterface::lowSpeedLimit = downloadLowSpeedLimitConfigurationOptional.getReference().m_lowSpeedLimit;
        curl::CurlInterface::lowSpeedTime = downloadLowSpeedLimitConfigurationOptional.getReference().m_lowSpeedTime;
    }
    if(configuration.isFileToBeDownloadUntilSuccessful())
    {
        isSuccessful = downloadBinaryFileUntilSuccessful<DownloadType::LowSpeedLimit, DownloadType::MozillaFireFox, DownloadType::PrintDownloadProgress>(fileToDownloadWebPathHandler, downloadPathHandler);
    }
    else
    {
        isSuccessful = downloadBinaryFileWithFiniteNumberOfTries<DownloadType::LowSpeedLimit, DownloadType::MozillaFireFox, DownloadType::PrintDownloadProgress>(fileToDownloadWebPathHandler, downloadPathHandler, configuration.getNumberOfRetries());
    }
    return isSuccessful;
}
bool Downloaders::downloadFileAsText(
        AlbaWebPathHandler const& fileToDownloadWebPathHandler,
        AlbaLocalPathHandler const& downloadPathHandler)
{
    return downloadUntilSuccessful<DownloadType::LowSpeedLimit, DownloadType::MozillaFireFox>(fileToDownloadWebPathHandler, downloadPathHandler);
}

void Downloaders::downloadFileUsingPhantomJs(        AlbaWebPathHandler const& fileToDownloadWebPathHandler,
        AlbaLocalPathHandler const& downloadPathHandler)
{
    AlbaLocalPathHandler const phantomJsFolder(PHANTOM_BIN_PATH);    string const command(phantomJsFolder.getFullPath()+"phantomjs.exe "+phantomJsFolder.getFullPath()+R"(loadPage.js ")"+fileToDownloadWebPathHandler.getFullPath()+R"(" ")"+downloadPathHandler.getFullPath()+R"(")");
    cout<<command<<endl;
    system(command.c_str());
}

}
