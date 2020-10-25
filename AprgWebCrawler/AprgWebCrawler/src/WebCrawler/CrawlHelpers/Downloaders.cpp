#include "Downloaders.hpp"

#include <CrawlConfiguration/CrawlConfiguration.hpp>
#include <CurlInterface.hpp>
#include <iostream>
#include <string>
#include <windows.h>

#define PHANTOM_BIN_PATH APRG_DIR R"(PhantomJs\PhantomJs\bin\)"

using namespace alba;
using namespace curl::CurlInterface;using namespace std;

namespace aprgWebCrawler
{
bool Downloaders::downloadBinaryFile(
        AlbaWebPathHandler const& fileToDownloadWebPathHandler,
        AlbaWindowsPathHandler const& downloadPathHandler,
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
        isSuccessful = downloadBinaryFileUntilSuccessful<DownloadType::LowSpeedLimitAndMozillaFireFoxAndPrintDownloadProgress>(fileToDownloadWebPathHandler, downloadPathHandler);
    }
    else
    {
        isSuccessful = downloadBinaryFileWithFiniteNumberOfTries<DownloadType::LowSpeedLimitAndMozillaFireFoxAndPrintDownloadProgress>(fileToDownloadWebPathHandler, downloadPathHandler, configuration.getNumberOfRetries());
    }
    return isSuccessful;
}

bool Downloaders::downloadFileAsText(
        AlbaWebPathHandler const& fileToDownloadWebPathHandler,
        AlbaWindowsPathHandler const& downloadPathHandler)
{
    return downloadUntilSuccessful<DownloadType::LowSpeedLimitAndMozillaFireFox>(fileToDownloadWebPathHandler, downloadPathHandler);
}

void Downloaders::downloadFileUsingPhantomJs(
        AlbaWebPathHandler const& fileToDownloadWebPathHandler,
        AlbaWindowsPathHandler const& downloadPathHandler)
{
    AlbaWindowsPathHandler const phantomJsFolder(PHANTOM_BIN_PATH);
    string const command(phantomJsFolder.getFullPath()+"phantomjs.exe "+phantomJsFolder.getFullPath()+R"(loadPage.js ")"+fileToDownloadWebPathHandler.getFullPath()+R"(" ")"+downloadPathHandler.getFullPath()+R"(")");
    cout<<command<<endl;
    system(command.c_str());
}

}
